using Sokoban_game.Properties;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Sokoban_game
{
    public partial class gameBoard : Form
    {
        private Vector2 gameSize;
        PictureBox[,] sprites;
        MenuForm menuForm;
        string inputFileDirectory;

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
                return;
            }
            gameSize = new Vector2(sizeX, sizeY);
            if (problemDataArray.Length - 2 < sizeY)
            {
                MessageBox.Show("Not enough rows are entered!", "Invalid Input");
                return;
            }
            for (int i = 2; i < problemDataArray.Length; i++)
            {
                if (problemDataArray[i].Length < sizeX)
                {
                    MessageBox.Show("Not enough columns are entered in row " + (i - 1).ToString() + "!", "Invalid Input");
                    return;
                }
            }
            allocate_sprites();
            for (int i = 0; i < GameSize.y; i++)
            {
                for(int j = 0; j < GameSize.x; j++)
                {
                    if(problemDataArray[i + 2][j] == '#')
                        sprites[j,i].Image = global::Sokoban_game.Properties.Resources.yoshi_32_wall;
                    else if(problemDataArray[i + 2][j] == '@')
                        sprites[j, i].Image = global::Sokoban_game.Properties.Resources.yoshi_32_box;
                    else if (problemDataArray[i + 2][j] == '.')
                        sprites[j, i].Image = global::Sokoban_game.Properties.Resources.yoshi_32_floor;
                    else if (problemDataArray[i + 2][j] == 'S')
                        sprites[j, i].Image = global::Sokoban_game.Properties.Resources.yoshi_32_worker;
                    else if (problemDataArray[i + 2][j] == 'X')
                        sprites[j, i].Image = global::Sokoban_game.Properties.Resources.yoshi_32_dock;
                }
            }
            ClientSize = new System.Drawing.Size(GameSize.x * 32, GameSize.y * 32);
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
        }

        private void boardForm_Closed(object sender, FormClosedEventArgs e)
        {
            menuForm.Show();
        }
    }
}

