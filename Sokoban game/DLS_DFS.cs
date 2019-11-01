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
    public partial class DLS_DFS : Form
    {
        gameBoard gameBoard;
        bool isParallel;
        public DLS_DFS(gameBoard _gameBoard, bool _isParallel)
        {
            InitializeComponent();
            gameBoard = _gameBoard;
            isParallel = _isParallel;
        }

        private void DFS_DLS_ProcessBtn_Click(object sender, EventArgs e)
        {
            this.Hide();
            Close();
            if (DFSRadio.Checked) {
                if (isParallel)
                    gameBoard.dfs_parallel();
                else
                    gameBoard.dfs();
            }
            else
            {
                if (isParallel)
                    gameBoard.dls_parallel(int.Parse(DLSText.Text));
                else
                    gameBoard.dls(int.Parse(DLSText.Text));
            }
        }

        private void DFSRadio_CheckedChanged(object sender, EventArgs e)
        {
            DLSText.Hide();
        }

        private void DLSRadio_CheckedChanged(object sender, EventArgs e)
        {
            DLSText.Show();
        }
    }
}
