namespace Sokoban_game
{
    partial class MenuForm
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
            this.InputBtn = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // InputBtn
            // 
            this.InputBtn.Location = new System.Drawing.Point(90, 124);
            this.InputBtn.Name = "InputBtn";
            this.InputBtn.Size = new System.Drawing.Size(75, 23);
            this.InputBtn.TabIndex = 0;
            this.InputBtn.Text = "Input";
            this.InputBtn.UseVisualStyleBackColor = true;
            this.InputBtn.Click += new System.EventHandler(this.InputBtn_Click);
            // 
            // MenuForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(275, 343);
            this.Controls.Add(this.InputBtn);
            this.Name = "MenuForm";
            this.Text = "Menu";
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button InputBtn;
    }
}