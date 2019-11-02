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
        List<Vector2> spotsLocations;
        float scaleFactor;
        string[] problemDataArray;
        SokobanSolver sokobanSolver;
        TextBox historySizeTextBox;

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
            scaleFactor = 1;
        }

        private void GameBoard_Load(object sender, EventArgs e)
        {
            string input = System.IO.File.ReadAllText(inputFileDirectory);
            parse_problem_data_str_into_board(input);

            this.SuspendLayout();

            var BFSBtn = new System.Windows.Forms.Button();
            BFSBtn.Location = new System.Drawing.Point(2, (int)(32 * GameSize.y * scaleFactor) + 8);
            BFSBtn.Name = "BFS";
            BFSBtn.Size = new System.Drawing.Size(74, 24);
            BFSBtn.TabIndex = 0;
            BFSBtn.Text = "BFS";
            BFSBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7);
            BFSBtn.UseVisualStyleBackColor = true;
            BFSBtn.Click += new System.EventHandler(BFS_Btn_click);

            var BFSParallelBtn = new System.Windows.Forms.Button();
            BFSParallelBtn.Location = new System.Drawing.Point(78, (int)(32 * GameSize.y * scaleFactor) + 8);
            BFSParallelBtn.Name = "BFSParallel";
            BFSParallelBtn.Size = new System.Drawing.Size(74, 24);
            BFSParallelBtn.TabIndex = 0;
            BFSParallelBtn.Text = "BFS Parallel";
            BFSParallelBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7);
            BFSParallelBtn.UseVisualStyleBackColor = true;
            BFSParallelBtn.Click += new System.EventHandler(BFS_Parallel_Btn_click);

            var DFSBtn = new System.Windows.Forms.Button();
            DFSBtn.Location = new System.Drawing.Point(154, (int)(32 * GameSize.y * scaleFactor) + 8);
            DFSBtn.Name = "DFS";
            DFSBtn.Size = new System.Drawing.Size(74, 24);
            DFSBtn.TabIndex = 0;
            DFSBtn.Text = "DFS";
            DFSBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7);
            DFSBtn.UseVisualStyleBackColor = true;
            DFSBtn.Click += new System.EventHandler(DFS_Btn_click);

            var DFSParallelBtn = new System.Windows.Forms.Button();
            DFSParallelBtn.Location = new System.Drawing.Point(230, (int)(32 * GameSize.y * scaleFactor) + 8);
            DFSParallelBtn.Name = "DFSParallel";
            DFSParallelBtn.Size = new System.Drawing.Size(74, 24);
            DFSParallelBtn.TabIndex = 0;
            DFSParallelBtn.Text = "DFS Parallel";
            DFSParallelBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7);
            DFSParallelBtn.UseVisualStyleBackColor = true;
            DFSParallelBtn.Click += new System.EventHandler(DFS_Parallel_Btn_click);

            var IDSBtn = new System.Windows.Forms.Button();
            IDSBtn.Location = new System.Drawing.Point(306, (int)(32 * GameSize.y * scaleFactor) + 8);
            IDSBtn.Name = "IDS";
            IDSBtn.Size = new System.Drawing.Size(74, 24);
            IDSBtn.TabIndex = 0;
            IDSBtn.Text = "IDS";
            IDSBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7);
            IDSBtn.UseVisualStyleBackColor = true;
            IDSBtn.Click += new System.EventHandler(IDS_Btn_click);

            var IDSParallelBtn = new System.Windows.Forms.Button();
            IDSParallelBtn.Location = new System.Drawing.Point(382, (int)(32 * GameSize.y * scaleFactor) + 8);
            IDSParallelBtn.Name = "IDS";
            IDSParallelBtn.Size = new System.Drawing.Size(74, 24);
            IDSParallelBtn.TabIndex = 0;
            IDSParallelBtn.Text = "IDS Parallel";
            IDSParallelBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7);
            IDSParallelBtn.UseVisualStyleBackColor = true;
            IDSParallelBtn.Click += new System.EventHandler(IDS_Parallel_Btn_click);

            var ResetBtn = new System.Windows.Forms.Button();
            ResetBtn.Location = new System.Drawing.Point(458, (int)(32 * GameSize.y * scaleFactor) + 8);
            ResetBtn.Name = "Reset";
            ResetBtn.Size = new System.Drawing.Size(74, 24);
            ResetBtn.TabIndex = 0;
            ResetBtn.Text = "Reset";
            ResetBtn.Font = new System.Drawing.Font("Microsoft Sans Serif", 7);
            ResetBtn.UseVisualStyleBackColor = true;
            ResetBtn.Click += new System.EventHandler(Reset_Btn_click);

            var historySizeLabel = new System.Windows.Forms.Label();
            historySizeLabel.Location = new System.Drawing.Point(4, (int)(32 * GameSize.y * scaleFactor) + 44);
            historySizeLabel.Name = "historySizeLabel";
            historySizeLabel.Size = new System.Drawing.Size(74, 24);
            historySizeLabel.TabIndex = 0;
            historySizeLabel.Text = "History size";
            historySizeLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 7);

            historySizeTextBox = new System.Windows.Forms.TextBox();
            historySizeTextBox.Location = new System.Drawing.Point(80, (int)(32 * GameSize.y * scaleFactor) + 42);
            historySizeTextBox.Name = "historySizeTextBoxs";
            historySizeTextBox.Size = new System.Drawing.Size(74, 24);
            historySizeTextBox.TabIndex = 0;
            historySizeTextBox.Text = "20000";
            historySizeTextBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 7);

            elapsedTimeLabel.Location = new System.Drawing.Point(534, (int)(32 * GameSize.y * scaleFactor) + 8);
            visitedNodesLabel.Location = new System.Drawing.Point(534, (int)(32 * GameSize.y * scaleFactor) + 20);

            this.ResumeLayout();
            this.Controls.Add(BFSBtn);
            this.Controls.Add(BFSParallelBtn);
            this.Controls.Add(DFSBtn);
            this.Controls.Add(DFSParallelBtn);
            this.Controls.Add(IDSBtn);
            this.Controls.Add(IDSParallelBtn);
            this.Controls.Add(ResetBtn);
            this.Controls.Add(historySizeLabel);
            this.Controls.Add(historySizeTextBox);
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

        private Task DoAsync(char x)
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
                await DoAsync(path[i]);
            }
        }

        private void BFS_Btn_click(object sender, EventArgs e)
        {
            sokobanSolver = new SokobanSolver(inputFileDirectory);
            uint historySize;
            if (!uint.TryParse(historySizeTextBox.Text, out historySize) || historySize < 1)
            {
                historySize = 1;
                historySizeTextBox.Text = "1";
            }
            char[] path = sokobanSolver.BFS(historySize).ToCharArray();
            elapsedTimeLabel.Text = "Elapsed time = " + sokobanSolver.LastProcessTimeElapsed() + "s";
            visitedNodesLabel.Text = "Visited nodes = " + sokobanSolver.LastProcessNodesCount();
            var task = Task.Run(async () => await showPath(path));
        }

        private void BFS_Parallel_Btn_click(object sender, EventArgs e)
        {
            sokobanSolver = new SokobanSolver(inputFileDirectory);
            uint historySize;
            if (!uint.TryParse(historySizeTextBox.Text, out historySize) || historySize < 1)
            {
                historySize = 1;
                historySizeTextBox.Text = "1";
            }
            char[] path = sokobanSolver.BFS_Parallel(historySize).ToCharArray();
            elapsedTimeLabel.Text = "Elapsed time = " + sokobanSolver.LastProcessTimeElapsed() + "s";
            visitedNodesLabel.Text = "Visited nodes = " + sokobanSolver.LastProcessNodesCount();
            var task = Task.Run(async () => await showPath(path));
        }

        private void DFS_Btn_click(object sender, EventArgs e)
        {
            DLS_DFS DLS_DFSForm = new DLS_DFS(this, false);
            DLS_DFSForm.ShowDialog();
        }

        private void DFS_Parallel_Btn_click(object sender, EventArgs e)
        {
            DLS_DFS DLS_DFSForm = new DLS_DFS(this, true);
            DLS_DFSForm.ShowDialog();
        }

        private void IDS_Btn_click(object sender, EventArgs e)
        {
            sokobanSolver = new SokobanSolver(inputFileDirectory);
            uint historySize;
            if (!uint.TryParse(historySizeTextBox.Text, out historySize) || historySize < 1)
            {
                historySize = 1;
                historySizeTextBox.Text = "1";
            }
            char[] path = sokobanSolver.IDS(historySize).ToCharArray();
            elapsedTimeLabel.Text = "Elapsed time = " + sokobanSolver.LastProcessTimeElapsed() + "s";
            visitedNodesLabel.Text = "Visited nodes = " + sokobanSolver.LastProcessNodesCount();
            var task = Task.Run(async () => await showPath(path));
        }

        private void IDS_Parallel_Btn_click(object sender, EventArgs e)
        {
            sokobanSolver = new SokobanSolver(inputFileDirectory);
            uint historySize;
            if (!uint.TryParse(historySizeTextBox.Text, out historySize) || historySize < 1)
            {
                historySize = 1;
                historySizeTextBox.Text = "1";
            }
            char[] path = sokobanSolver.IDS_Parallel(historySize).ToCharArray();
            elapsedTimeLabel.Text = "Elapsed time = " + sokobanSolver.LastProcessTimeElapsed() + "s";
            visitedNodesLabel.Text = "Visited nodes = " + sokobanSolver.LastProcessNodesCount();
            var task = Task.Run(async () => await showPath(path));
        }

        private void Reset_Btn_click(object sender, EventArgs e)
        {
            if (sokobanSolver != null)
            {
                sokobanSolver = null;
                GC.Collect();
            }
            boxesLocations.Clear();
            spotsLocations.Clear();
            for (int i = 0; i < GameSize.y; i++)
            {
                for (int j = 0; j < GameSize.x; j++)
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
                    {
                        spotsLocations.Add(new Vector2(j, i));
                        sprites[j, i].Image = global::Sokoban_game.Properties.Resources.yoshi_32_dock;
                    }
                }
            }
        }

        public void dfs()
        {
            sokobanSolver = new SokobanSolver(inputFileDirectory);
            uint historySize;
            if (!uint.TryParse(historySizeTextBox.Text, out historySize) || historySize < 1)
            {
                historySize = 1;
                historySizeTextBox.Text = "1";
            }
            char[] path = sokobanSolver.DFS(historySize).ToCharArray();
            elapsedTimeLabel.Text = "Elapsed time = " + sokobanSolver.LastProcessTimeElapsed() + "s";
            visitedNodesLabel.Text = "Visited nodes = " + sokobanSolver.LastProcessNodesCount();
            var task = Task.Run(async () => await showPath(path));
        }

        public void dls(int depth)
        {
            sokobanSolver = new SokobanSolver(inputFileDirectory);
            uint historySize;
            if (!uint.TryParse(historySizeTextBox.Text, out historySize) || historySize < 1)
            {
                historySize = 1;
                historySizeTextBox.Text = "1";
            }
            char[] path = sokobanSolver.DFS(depth, historySize).ToCharArray();
            elapsedTimeLabel.Text = "Elapsed time = " + sokobanSolver.LastProcessTimeElapsed() + "s";
            visitedNodesLabel.Text = "Visited nodes = " + sokobanSolver.LastProcessNodesCount();
            var task = Task.Run(async () => await showPath(path));
        }

        public void dfs_parallel()
        {
            sokobanSolver = new SokobanSolver(inputFileDirectory);
            uint historySize;
            if (!uint.TryParse(historySizeTextBox.Text, out historySize) || historySize < 1)
            {
                historySize = 1;
                historySizeTextBox.Text = "1";
            }
            char[] path = sokobanSolver.DFS_Parallel(historySize).ToCharArray();
            elapsedTimeLabel.Text = "Elapsed time = " + sokobanSolver.LastProcessTimeElapsed() + "s";
            visitedNodesLabel.Text = "Visited nodes = " + sokobanSolver.LastProcessNodesCount();
            var task = Task.Run(async () => await showPath(path));
        }

        public void dls_parallel(int depth)
        {
            sokobanSolver = new SokobanSolver(inputFileDirectory);
            uint historySize;
            if (!uint.TryParse(historySizeTextBox.Text, out historySize) || historySize < 1)
            {
                historySize = 1;
                historySizeTextBox.Text = "1";
            }
            char[] path = sokobanSolver.DFS_Parallel(depth, historySize).ToCharArray();
            elapsedTimeLabel.Text = "Elapsed time = " + sokobanSolver.LastProcessTimeElapsed() + "s";
            visitedNodesLabel.Text = "Visited nodes = " + sokobanSolver.LastProcessNodesCount();
            var task = Task.Run(async () => await showPath(path));
        }

        private void parse_problem_data_str_into_board(string problemDataStr)
        {
            char[] separator = null;
            problemDataArray = problemDataStr.Split(separator, System.StringSplitOptions.RemoveEmptyEntries);
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
            int width = GameSize.x * 32;
            int height = GameSize.y * 32;
            if (width > 1200 || height > 900)
            {
                int scaleRatioX = width / 1200;
                int scaleRatioY = height / 900;
                scaleFactor = 1 / (float)Math.Max(scaleRatioX + 1, scaleRatioY + 1);
            }
            width = (int)(width * scaleFactor);
            height = (int)(height * scaleFactor);
            int offsetX = 0; 
            if (width < 650)
            {
                offsetX = (650 % width) / 2;
                width = 650;
            }
            height += 70;
            allocate_sprites(offsetX);
            boxesLocations = new List<Vector2>();
            spotsLocations = new List<Vector2>();
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
                    {
                        spotsLocations.Add(new Vector2(j, i));
                        sprites[j, i].Image = global::Sokoban_game.Properties.Resources.yoshi_32_dock;
                    }
                }
            }
            ClientSize = new System.Drawing.Size(width, height);
            ResumeLayout();
        }

        private void allocate_sprites(int offsetX)
        {
            sprites = new PictureBox[GameSize.x, GameSize.y];
            for(int i = 0; i < GameSize.x; i++)
            {
                for (int j = 0; j < GameSize.y; j++)
                {
                    sprites[i, j] = new PictureBox();
                    sprites[i, j].Location = new System.Drawing.Point((int)(offsetX + 32 * scaleFactor * i), (int)(32 * scaleFactor * j));
                    sprites[i, j].Name = "sprite +" + i.ToString() + "_" + j.ToString();
                    sprites[i, j].Size = new System.Drawing.Size((int)(32 * scaleFactor), (int)(32 * scaleFactor));
                    sprites[i, j].TabIndex = 0;
                    sprites[i, j].TabStop = false;
                    sprites[i, j].SizeMode = PictureBoxSizeMode.StretchImage;
                    ((System.ComponentModel.ISupportInitialize)(sprites[i, j])).EndInit();
                    this.Controls.Add(sprites[i, j]);
                }
            }
        }

        public class Vector2: IEquatable<Vector2>
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
            public static bool operator ==(Vector2 a, Vector2 b)
            {
                return a.x == b.x && a.y == b.y;
            }
            public static bool operator !=(Vector2 a, Vector2 b)
            {
                return !(a == b);
            }
            public bool Equals(Vector2 other)
            {
                return this == other;
            }
        }

        private void boardForm_Closed(object sender, FormClosedEventArgs e)
        {
            menuForm.Show();
        }

        private void swap_sprites(Vector2 index1, Vector2 index2)
        {
            if (spotsLocations.Contains(index2))
            {
                sprites[index2.x, index2.y].Image = sprites[index2.x, index2.y].Image = global::Sokoban_game.Properties.Resources.yoshi_32_floor;
                spotsLocations.Remove(index2);
            }
            Image temp = sprites[index1.x, index1.y].Image;
            sprites[index1.x, index1.y].Image = sprites[index2.x, index2.y].Image;
            sprites[index2.x, index2.y].Image = temp;
        }
    }
}

