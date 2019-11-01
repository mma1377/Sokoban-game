namespace Sokoban_game
{
    partial class DLS_DFS
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
            this.DFS_DLS_ProcessBtn = new System.Windows.Forms.Button();
            this.DLSText = new System.Windows.Forms.TextBox();
            this.DLSRadio = new System.Windows.Forms.RadioButton();
            this.DFSRadio = new System.Windows.Forms.RadioButton();
            this.SuspendLayout();
            // 
            // DFS_DLS_ProcessBtn
            // 
            this.DFS_DLS_ProcessBtn.Location = new System.Drawing.Point(12, 113);
            this.DFS_DLS_ProcessBtn.Name = "DFS_DLS_ProcessBtn";
            this.DFS_DLS_ProcessBtn.Size = new System.Drawing.Size(75, 23);
            this.DFS_DLS_ProcessBtn.TabIndex = 1;
            this.DFS_DLS_ProcessBtn.Text = "Process";
            this.DFS_DLS_ProcessBtn.UseVisualStyleBackColor = true;
            this.DFS_DLS_ProcessBtn.Click += new System.EventHandler(this.DFS_DLS_ProcessBtn_Click);
            // 
            // DLSText
            // 
            this.DLSText.Location = new System.Drawing.Point(109, 51);
            this.DLSText.Name = "DLSText";
            this.DLSText.Size = new System.Drawing.Size(100, 20);
            this.DLSText.TabIndex = 2;
            this.DLSText.Text = "10";
            // 
            // DLSRadio
            // 
            this.DLSRadio.AutoSize = true;
            this.DLSRadio.Checked = true;
            this.DLSRadio.Location = new System.Drawing.Point(21, 51);
            this.DLSRadio.Name = "DLSRadio";
            this.DLSRadio.Size = new System.Drawing.Size(46, 17);
            this.DLSRadio.TabIndex = 3;
            this.DLSRadio.TabStop = true;
            this.DLSRadio.Text = "DLS";
            this.DLSRadio.UseVisualStyleBackColor = true;
            this.DLSRadio.CheckedChanged += new System.EventHandler(this.DLSRadio_CheckedChanged);
            // 
            // DFSRadio
            // 
            this.DFSRadio.AutoSize = true;
            this.DFSRadio.Location = new System.Drawing.Point(21, 75);
            this.DFSRadio.Name = "DFSRadio";
            this.DFSRadio.Size = new System.Drawing.Size(46, 17);
            this.DFSRadio.TabIndex = 4;
            this.DFSRadio.TabStop = true;
            this.DFSRadio.Text = "DFS";
            this.DFSRadio.UseVisualStyleBackColor = true;
            this.DFSRadio.CheckedChanged += new System.EventHandler(this.DFSRadio_CheckedChanged);
            // 
            // DLS_DFS
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(227, 148);
            this.Controls.Add(this.DFSRadio);
            this.Controls.Add(this.DLSRadio);
            this.Controls.Add(this.DLSText);
            this.Controls.Add(this.DFS_DLS_ProcessBtn);
            this.Name = "DLS_DFS";
            this.Text = "DLS_DFS";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button DFS_DLS_ProcessBtn;
        private System.Windows.Forms.TextBox DLSText;
        private System.Windows.Forms.RadioButton DLSRadio;
        private System.Windows.Forms.RadioButton DFSRadio;
    }
}