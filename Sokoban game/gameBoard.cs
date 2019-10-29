﻿using Sokoban_game.Properties;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using IronPython.Hosting;
using IronPython;
using SOKOBAN;
using System.Threading;

namespace Sokoban_game
{

    public partial class gameBoard : Form
    {
        private Vector2 gameSize;
        PictureBox[,] sprites;
        MenuForm menuForm;
        string inputFileDirectory;
        Vector2 playerPosition;
        List<Vector2> boxesLocations;
        //dynamic SOKOBAN;

        public Vector2 GameSize
        {
            get
            {
                return gameSize;
            }
        }

        public gameBoard(MenuForm _menuForm, string _inputFileDirectory)
        {
            InitializeComponent();
            menuForm = _menuForm;
            inputFileDirectory = _inputFileDirectory;
        }

        private void GameBoard_Load(object sender, EventArgs e)
        {
            string input = System.IO.File.ReadAllText(inputFileDirectory);
            parse_problem_data_str_into_board(input);
            var processBtn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            processBtn.Location = new System.Drawing.Point(8, 32 * GameSize.y + 8);
            processBtn.Name = "processBtn";
            processBtn.Size = new System.Drawing.Size(64, 24);
            processBtn.TabIndex = 0;
            processBtn.Text = "Process";
            processBtn.UseVisualStyleBackColor = true;
            processBtn.Click += new System.EventHandler(processBtn_click);
            this.ResumeLayout();
            this.Controls.Add(processBtn);
        }

        private bool isBox(Vector2 position, ref int index)
        {
            for(int i = 0; i < boxesLocations.Count; i++)
            {
                if (boxesLocations[i].x == position.x && boxesLocations[i].y == position.y)
                {
                    index = i;
                    return true;
                }
            }
            return false;
        }

        private Task DoAsync(char x, int i)
        {
            Task.Delay(300).Wait();
            switch (x)
            {
                case 'U':
                    Vector2 newPos = playerPosition + new Vector2(0, -1);
                    int BoxIndx = 0;
                    if (isBox(newPos, ref BoxIndx))
                    {
                        swap_sprites(newPos, newPos + new Vector2(0, -1));
                        boxesLocations[BoxIndx] = newPos + new Vector2(0, -1);
                    }
                    swap_sprites(playerPosition, newPos);
                    playerPosition = newPos;
                    break;
                case 'D':
                    newPos = playerPosition + new Vector2(0, 1);
                    BoxIndx = 0;
                    if (isBox(newPos, ref BoxIndx))
                    {
                        swap_sprites(newPos, newPos + new Vector2(0, 1));
                        boxesLocations[BoxIndx] = newPos + new Vector2(0, 1);
                    }
                    swap_sprites(playerPosition, newPos);
                    playerPosition = newPos;
                    break;
                case 'L':
                    newPos = playerPosition + new Vector2(-1, 0);
                    BoxIndx = 0;
                    if (isBox(newPos, ref BoxIndx))
                    {
                        swap_sprites(newPos, newPos + new Vector2(-1, 0));
                        boxesLocations[BoxIndx] = newPos + new Vector2(-1, 0);
                    }
                    swap_sprites(playerPosition, newPos);
                    playerPosition = newPos;
                    break;
                case 'R':
                    newPos = playerPosition + new Vector2(1, 0);
                    BoxIndx = 0;
                    if (isBox(newPos, ref BoxIndx))
                    {
                        swap_sprites(newPos, newPos + new Vector2(1, 0));
                        boxesLocations[BoxIndx] = newPos + new Vector2(1, 0);
                    }
                    swap_sprites(playerPosition, newPos);
                    playerPosition = newPos;
                    break;
            }
            return Task.CompletedTask;
        }

        private async Task showPath(char[] path)
        {
            for (int i = 0; i < path.Length; i++)
            {
                await DoAsync(path[i], i);
            }
        }

        private void processBtn_click(object sender, EventArgs e)
        {
            SokobanSolver sokobanSolver = new SokobanSolver(inputFileDirectory);
            char[] path = "RRRRRDRULUR".ToCharArray();//= sokobanSolver.BFS().ToCharArray();
            //char[] path = "RR".ToCharArray();//= sokobanSolver.BFS().ToCharArray();
            var task = Task.Run(async () => await showPath(path));
            //MessageBox.Show(sokobanSolver.test().ToString());
            //MessageBox.Show("test");
            //\sokoban-cpp\Sokoban\Release
            //var engine = Python.CreateEngine();
            //dynamic py = engine.ExecuteFile(System.IO.Directory.GetParent(System.IO.Directory.GetCurrentDirectory()).Parent.Parent.FullName + "\\sokoban-python\\sokoban.py");
            //SOKOBAN = py.SOKOBAN(inputFileDirectory);
            //List<IronPython.Runtime.PythonTuple> res = SOKOBAN.test();
            //for(int i = 0; i < res.Count; i++)
            //{
            //    var agentPos = ((IronPython.Runtime.PythonTuple)res[i].__getslice__(0, 0));
            //    var boxPos = ((IronPython.Runtime.PythonTuple)res[i].__getslice__(1, 1));
            //    MessageBox.Show(((int)agentPos.__getslice__(0, 0)).ToString());
            //    //Timer timer1 = new Timer
            //    //{
            //    //    Interval = 1000
            //    //};
            //    //timer1.Enabled = true;
            //    //timer1.Tick += new System.EventHandler(OnTimerEvent);
            //}
        }

        private void OnTimerEvent(object sender, EventArgs e)
        {
            
        }

        private void parse_problem_data_str_into_board(string problemDataStr)
        {
            char[] separator = null;
            string[] problemDataArray = problemDataStr.Split(separator, System.StringSplitOptions.RemoveEmptyEntries);
            int sizeX = default, sizeY = default;
            bool validInputSize = int.TryParse(problemDataArray[0], out sizeY) && int.TryParse(problemDataArray[1], out sizeX);
            if (!validInputSize)
            {
                MessageBox.Show("2 first elements in input demonstrate game size!\nPlease check that they are entered correctly.", "Invalid Input");
                this.Close();
                return;
            }
            gameSize = new Vector2(sizeX, sizeY);
            if (problemDataArray.Length - 2 < sizeY)
            {
                MessageBox.Show("Not enough rows are entered!", "Invalid Input");
                this.Close();
                return;
            }
            for (int i = 2; i < problemDataArray.Length; i++)
            {
                if (problemDataArray[i].Length < sizeX)
                {
                    MessageBox.Show("Not enough columns are entered in row " + (i - 1).ToString() + "!", "Invalid Input");
                    this.Close();
                    return;
                }
            }
            allocate_sprites();
            boxesLocations = new List<Vector2>();
            for (int i = 0; i < GameSize.y; i++)
            {
                for(int j = 0; j < GameSize.x; j++)
                {
                    if (problemDataArray[i + 2][j] == '#')
                        sprites[j, i].Image = global::Sokoban_game.Properties.Resources.yoshi_32_wall;
                    else if (problemDataArray[i + 2][j] == '@')
                    {
                        boxesLocations.Add(new Vector2(j, i));
                        sprites[j, i].Image = global::Sokoban_game.Properties.Resources.yoshi_32_box;
                    }
                    else if (problemDataArray[i + 2][j] == '.')
                        sprites[j, i].Image = global::Sokoban_game.Properties.Resources.yoshi_32_floor;
                    else if (problemDataArray[i + 2][j] == 'S')
                    {
                        sprites[j, i].Image = global::Sokoban_game.Properties.Resources.yoshi_32_worker;
                        playerPosition = new Vector2(j, i);
                    }
                    else if (problemDataArray[i + 2][j] == 'X')
                        sprites[j, i].Image = global::Sokoban_game.Properties.Resources.yoshi_32_dock;
                }
            }
            ClientSize = new System.Drawing.Size(GameSize.x * 32, GameSize.y * 32 + 40);
            ResumeLayout();
        }

        private void allocate_sprites()
        {
            sprites = new PictureBox[GameSize.x, GameSize.y];
            for(int i = 0; i < GameSize.x; i++)
            {
                for (int j = 0; j < GameSize.y; j++)
                {
                    sprites[i, j] = new PictureBox();
                    sprites[i, j].Location = new System.Drawing.Point(32 * i, 32 * j);
                    sprites[i, j].Name = "sprite +" + i.ToString() + "_" + j.ToString();
                    sprites[i, j].Size = new System.Drawing.Size(32, 32);
                    sprites[i, j].TabIndex = 0;
                    sprites[i, j].TabStop = false;
                    ((System.ComponentModel.ISupportInitialize)(sprites[i, j])).EndInit();
                    this.Controls.Add(sprites[i, j]);
                }
            }
        }

        public class Vector2
        {
            int _x;
            int _y;
            public int x
            {
                get
                {
                    return _x;
                }
            }
            public int y
            {
                get
                {
                    return _y;
                }
            }
            public Vector2(int x, int y)
            {
                _x = x;
                _y = y;
            }
            public static Vector2 operator +(Vector2 a, Vector2 b)
            {
                return new Vector2(a.x + b.x, a.y + b.y);
            }
        }

        private void boardForm_Closed(object sender, FormClosedEventArgs e)
        {
            menuForm.Show();
        }

        private void swap_sprites(Vector2 index1, Vector2 index2)
        {
            Image temp = sprites[index1.x, index1.y].Image;
            sprites[index1.x, index1.y].Image = sprites[index2.x, index2.y].Image;
            sprites[index2.x, index2.y].Image = temp;
        }
    }
}

