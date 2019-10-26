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
    public partial class MenuForm : Form
    {
        public MenuForm()
        {
            InitializeComponent();
        }

        private void InputBtn_Click(object sender, EventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
            openFileDialog.DefaultExt = ".txt";
            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                gameBoard board = new gameBoard(this, openFileDialog.FileName);
                Hide();
                board.ShowDialog();
            }
        }
    }
}
