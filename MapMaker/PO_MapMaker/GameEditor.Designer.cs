namespace PO_MapMaker
{
    partial class GameEditor
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
            this.label5 = new System.Windows.Forms.Label();
            this.GameWidth = new System.Windows.Forms.TextBox();
            this.EnableDebug = new System.Windows.Forms.CheckBox();
            this.label3 = new System.Windows.Forms.Label();
            this.saveGameAttrs = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.GameHeight = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(12, 9);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(76, 13);
            this.label5.TabIndex = 39;
            this.label5.Text = "Game Width";
            // 
            // GameWidth
            // 
            this.GameWidth.Location = new System.Drawing.Point(12, 25);
            this.GameWidth.Name = "GameWidth";
            this.GameWidth.Size = new System.Drawing.Size(130, 20);
            this.GameWidth.TabIndex = 38;
            // 
            // EnableDebug
            // 
            this.EnableDebug.AutoSize = true;
            this.EnableDebug.Location = new System.Drawing.Point(12, 64);
            this.EnableDebug.Name = "EnableDebug";
            this.EnableDebug.Size = new System.Drawing.Size(130, 17);
            this.EnableDebug.TabIndex = 30;
            this.EnableDebug.Text = "Enable debug outputs";
            this.EnableDebug.UseVisualStyleBackColor = true;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(9, 48);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(68, 13);
            this.label3.TabIndex = 29;
            this.label3.Text = "Debugging";
            // 
            // saveGameAttrs
            // 
            this.saveGameAttrs.Location = new System.Drawing.Point(12, 87);
            this.saveGameAttrs.Name = "saveGameAttrs";
            this.saveGameAttrs.Size = new System.Drawing.Size(266, 26);
            this.saveGameAttrs.TabIndex = 24;
            this.saveGameAttrs.Text = "Save";
            this.saveGameAttrs.UseVisualStyleBackColor = true;
            this.saveGameAttrs.Click += new System.EventHandler(this.saveGameAttrs_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(148, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(80, 13);
            this.label1.TabIndex = 41;
            this.label1.Text = "Game Height";
            // 
            // GameHeight
            // 
            this.GameHeight.Location = new System.Drawing.Point(148, 25);
            this.GameHeight.Name = "GameHeight";
            this.GameHeight.Size = new System.Drawing.Size(130, 20);
            this.GameHeight.TabIndex = 40;
            // 
            // GameEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(290, 122);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.GameHeight);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.GameWidth);
            this.Controls.Add(this.EnableDebug);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.saveGameAttrs);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "GameEditor";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Modify Game Configuration";
            this.Load += new System.EventHandler(this.GameEditor_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox GameWidth;
        private System.Windows.Forms.CheckBox EnableDebug;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button saveGameAttrs;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox GameHeight;
    }
}