namespace PO_MapMaker
{
    partial class TileSetEditor
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
            this.addSet = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.tileSetName = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // addSet
            // 
            this.addSet.Location = new System.Drawing.Point(15, 51);
            this.addSet.Name = "addSet";
            this.addSet.Size = new System.Drawing.Size(249, 26);
            this.addSet.TabIndex = 2;
            this.addSet.Text = "Add Set";
            this.addSet.UseVisualStyleBackColor = true;
            this.addSet.Click += new System.EventHandler(this.addSet_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(87, 13);
            this.label1.TabIndex = 19;
            this.label1.Text = "Tile Set Name";
            // 
            // tileSetName
            // 
            this.tileSetName.CharacterCasing = System.Windows.Forms.CharacterCasing.Upper;
            this.tileSetName.Location = new System.Drawing.Point(15, 25);
            this.tileSetName.Name = "tileSetName";
            this.tileSetName.Size = new System.Drawing.Size(249, 20);
            this.tileSetName.TabIndex = 1;
            // 
            // TileSetEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(280, 87);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.tileSetName);
            this.Controls.Add(this.addSet);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "TileSetEditor";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Add New Tile Set...";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button addSet;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox tileSetName;
    }
}