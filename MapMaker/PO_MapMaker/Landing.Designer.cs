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
            this.openGameEditor = new System.Windows.Forms.Button();
            this.openCharacterEditor = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // openTileEditor
            // 
            this.openTileEditor.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.openTileEditor.Location = new System.Drawing.Point(6, 19);
            this.openTileEditor.Name = "openTileEditor";
            this.openTileEditor.Size = new System.Drawing.Size(262, 36);
            this.openTileEditor.TabIndex = 0;
            this.openTileEditor.Text = "Tile Editor";
            this.openTileEditor.UseVisualStyleBackColor = true;
            this.openTileEditor.Click += new System.EventHandler(this.openTileEditor_Click);
            // 
            // openRoomEditor
            // 
            this.openRoomEditor.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.openRoomEditor.Location = new System.Drawing.Point(6, 61);
            this.openRoomEditor.Name = "openRoomEditor";
            this.openRoomEditor.Size = new System.Drawing.Size(262, 36);
            this.openRoomEditor.TabIndex = 1;
            this.openRoomEditor.Text = "Room Editor";
            this.openRoomEditor.UseVisualStyleBackColor = true;
            this.openRoomEditor.Click += new System.EventHandler(this.openRoomEditor_Click);
            // 
            // openMapEditor
            // 
            this.openMapEditor.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.openMapEditor.Location = new System.Drawing.Point(6, 103);
            this.openMapEditor.Name = "openMapEditor";
            this.openMapEditor.Size = new System.Drawing.Size(262, 36);
            this.openMapEditor.TabIndex = 2;
            this.openMapEditor.Text = "Map Editor";
            this.openMapEditor.UseVisualStyleBackColor = true;
            // 
            // startCompile
            // 
            this.startCompile.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.startCompile.Location = new System.Drawing.Point(12, 295);
            this.startCompile.Name = "startCompile";
            this.startCompile.Size = new System.Drawing.Size(274, 49);
            this.startCompile.TabIndex = 3;
            this.startCompile.Text = "Compile Changes";
            this.startCompile.UseVisualStyleBackColor = true;
            this.startCompile.Click += new System.EventHandler(this.startCompile_Click);
            // 
            // openGameEditor
            // 
            this.openGameEditor.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.openGameEditor.Location = new System.Drawing.Point(6, 19);
            this.openGameEditor.Name = "openGameEditor";
            this.openGameEditor.Size = new System.Drawing.Size(262, 36);
            this.openGameEditor.TabIndex = 4;
            this.openGameEditor.Text = "Game Editor";
            this.openGameEditor.UseVisualStyleBackColor = true;
            this.openGameEditor.Click += new System.EventHandler(this.openGameEditor_Click);
            // 
            // openCharacterEditor
            // 
            this.openCharacterEditor.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.openCharacterEditor.Location = new System.Drawing.Point(6, 19);
            this.openCharacterEditor.Name = "openCharacterEditor";
            this.openCharacterEditor.Size = new System.Drawing.Size(262, 36);
            this.openCharacterEditor.TabIndex = 5;
            this.openCharacterEditor.Text = "Character Editor";
            this.openCharacterEditor.UseVisualStyleBackColor = true;
            this.openCharacterEditor.Click += new System.EventHandler(this.openCharacterEditor_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.openTileEditor);
            this.groupBox1.Controls.Add(this.openRoomEditor);
            this.groupBox1.Controls.Add(this.openMapEditor);
            this.groupBox1.Location = new System.Drawing.Point(12, 12);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(274, 145);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Level Editor";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.openGameEditor);
            this.groupBox2.Location = new System.Drawing.Point(12, 229);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(274, 60);
            this.groupBox2.TabIndex = 7;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Misc Game Configurations";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.openCharacterEditor);
            this.groupBox3.Location = new System.Drawing.Point(12, 163);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(274, 60);
            this.groupBox3.TabIndex = 8;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Character Editor";
            // 
            // Landing
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(298, 353);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.startCompile);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "Landing";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Planned Obsolescence Editor";
            this.Load += new System.EventHandler(this.Landing_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button openTileEditor;
        private System.Windows.Forms.Button openRoomEditor;
        private System.Windows.Forms.Button openMapEditor;
        private System.Windows.Forms.Button startCompile;
        private System.Windows.Forms.Button openGameEditor;
        private System.Windows.Forms.Button openCharacterEditor;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox3;
    }
}

