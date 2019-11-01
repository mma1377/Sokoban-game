namespace Sokoban_game
{
    partial class gameBoard
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.elapsedTimeLabel = new System.Windows.Forms.Label();
            this.visitedNodesLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // elapsedTimeLabel
            // 
            this.elapsedTimeLabel.AutoSize = true;
            this.elapsedTimeLabel.Location = new System.Drawing.Point(386, 222);
            this.elapsedTimeLabel.Name = "elapsedTimeLabel";
            this.elapsedTimeLabel.Size = new System.Drawing.Size(0, 13);
            this.elapsedTimeLabel.TabIndex = 0;
            // 
            // visitedNodesLabel
            // 
            this.visitedNodesLabel.AutoSize = true;
            this.visitedNodesLabel.Location = new System.Drawing.Point(400, 219);
            this.visitedNodesLabel.Name = "visitedNodesLabel";
            this.visitedNodesLabel.Size = new System.Drawing.Size(0, 13);
            this.visitedNodesLabel.TabIndex = 1;
            // 
            // gameBoard
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.visitedNodesLabel);
            this.Controls.Add(this.elapsedTimeLabel);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "gameBoard";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Sokoban";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.boardForm_Closed);
            this.Load += new System.EventHandler(this.GameBoard_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label elapsedTimeLabel;
        private System.Windows.Forms.Label visitedNodesLabel;
    }
}

