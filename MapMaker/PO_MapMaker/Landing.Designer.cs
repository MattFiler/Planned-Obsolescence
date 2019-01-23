namespace PO_MapMaker
{
    partial class Landing
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
            this.openTileEditor = new System.Windows.Forms.Button();
            this.openRoomEditor = new System.Windows.Forms.Button();
            this.openMapEditor = new System.Windows.Forms.Button();
            this.startCompile = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // openTileEditor
            // 
            this.openTileEditor.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.openTileEditor.Location = new System.Drawing.Point(12, 12);
            this.openTileEditor.Name = "openTileEditor";
            this.openTileEditor.Size = new System.Drawing.Size(145, 122);
            this.openTileEditor.TabIndex = 0;
            this.openTileEditor.Text = "Tile Editor";
            this.openTileEditor.UseVisualStyleBackColor = true;
            this.openTileEditor.Click += new System.EventHandler(this.openTileEditor_Click);
            // 
            // openRoomEditor
            // 
            this.openRoomEditor.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.openRoomEditor.Location = new System.Drawing.Point(163, 12);
            this.openRoomEditor.Name = "openRoomEditor";
            this.openRoomEditor.Size = new System.Drawing.Size(145, 122);
            this.openRoomEditor.TabIndex = 1;
            this.openRoomEditor.Text = "Room Editor";
            this.openRoomEditor.UseVisualStyleBackColor = true;
            // 
            // openMapEditor
            // 
            this.openMapEditor.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.openMapEditor.Location = new System.Drawing.Point(314, 12);
            this.openMapEditor.Name = "openMapEditor";
            this.openMapEditor.Size = new System.Drawing.Size(145, 122);
            this.openMapEditor.TabIndex = 2;
            this.openMapEditor.Text = "Map Editor";
            this.openMapEditor.UseVisualStyleBackColor = true;
            // 
            // startCompile
            // 
            this.startCompile.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.startCompile.Location = new System.Drawing.Point(12, 140);
            this.startCompile.Name = "startCompile";
            this.startCompile.Size = new System.Drawing.Size(447, 52);
            this.startCompile.TabIndex = 3;
            this.startCompile.Text = "Compile Changes";
            this.startCompile.UseVisualStyleBackColor = true;
            // 
            // Landing
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(471, 204);
            this.Controls.Add(this.startCompile);
            this.Controls.Add(this.openMapEditor);
            this.Controls.Add(this.openRoomEditor);
            this.Controls.Add(this.openTileEditor);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "Landing";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Planned Obsolescence Editor";
            this.Load += new System.EventHandler(this.Landing_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button openTileEditor;
        private System.Windows.Forms.Button openRoomEditor;
        private System.Windows.Forms.Button openMapEditor;
        private System.Windows.Forms.Button startCompile;
    }
}

