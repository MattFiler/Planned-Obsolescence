namespace PO_MapMaker
{
    partial class TileEditor
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
            this.addTile = new System.Windows.Forms.Button();
            this.tileSprite = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.tileSet = new System.Windows.Forms.ComboBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.POI_Computer = new System.Windows.Forms.CheckBox();
            this.POI_Door = new System.Windows.Forms.CheckBox();
            this.EXIT_Right = new System.Windows.Forms.CheckBox();
            this.EXIT_Left = new System.Windows.Forms.CheckBox();
            this.label4 = new System.Windows.Forms.Label();
            this.EXIT_Up = new System.Windows.Forms.CheckBox();
            this.EXIT_Down = new System.Windows.Forms.CheckBox();
            this.browseFile = new System.Windows.Forms.Button();
            this.tileName = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.tileWidth = new System.Windows.Forms.TextBox();
            this.tileHeight = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.defaultSizes = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // addTile
            // 
            this.addTile.Location = new System.Drawing.Point(12, 241);
            this.addTile.Name = "addTile";
            this.addTile.Size = new System.Drawing.Size(249, 26);
            this.addTile.TabIndex = 0;
            this.addTile.Text = "Add Tile";
            this.addTile.UseVisualStyleBackColor = true;
            this.addTile.Click += new System.EventHandler(this.button1_Click);
            // 
            // tileSprite
            // 
            this.tileSprite.Location = new System.Drawing.Point(12, 104);
            this.tileSprite.Name = "tileSprite";
            this.tileSprite.ReadOnly = true;
            this.tileSprite.Size = new System.Drawing.Size(169, 20);
            this.tileSprite.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(9, 88);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 13);
            this.label1.TabIndex = 2;
            this.label1.Text = "Tile Sprite";
            // 
            // tileSet
            // 
            this.tileSet.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.tileSet.FormattingEnabled = true;
            this.tileSet.Location = new System.Drawing.Point(12, 64);
            this.tileSet.Name = "tileSet";
            this.tileSet.Size = new System.Drawing.Size(249, 21);
            this.tileSet.TabIndex = 4;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(9, 48);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(51, 13);
            this.label2.TabIndex = 5;
            this.label2.Text = "Tile Set";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(9, 166);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(104, 13);
            this.label3.TabIndex = 8;
            this.label3.Text = "Points of Interest";
            // 
            // POI_Computer
            // 
            this.POI_Computer.AutoSize = true;
            this.POI_Computer.Location = new System.Drawing.Point(12, 182);
            this.POI_Computer.Name = "POI_Computer";
            this.POI_Computer.Size = new System.Drawing.Size(71, 17);
            this.POI_Computer.TabIndex = 9;
            this.POI_Computer.Text = "Computer";
            this.POI_Computer.UseVisualStyleBackColor = true;
            // 
            // POI_Door
            // 
            this.POI_Door.AutoSize = true;
            this.POI_Door.Location = new System.Drawing.Point(89, 182);
            this.POI_Door.Name = "POI_Door";
            this.POI_Door.Size = new System.Drawing.Size(49, 17);
            this.POI_Door.TabIndex = 10;
            this.POI_Door.Text = "Door";
            this.POI_Door.UseVisualStyleBackColor = true;
            // 
            // EXIT_Right
            // 
            this.EXIT_Right.AutoSize = true;
            this.EXIT_Right.Location = new System.Drawing.Point(62, 218);
            this.EXIT_Right.Name = "EXIT_Right";
            this.EXIT_Right.Size = new System.Drawing.Size(51, 17);
            this.EXIT_Right.TabIndex = 13;
            this.EXIT_Right.Text = "Right";
            this.EXIT_Right.UseVisualStyleBackColor = true;
            // 
            // EXIT_Left
            // 
            this.EXIT_Left.AutoSize = true;
            this.EXIT_Left.Location = new System.Drawing.Point(12, 218);
            this.EXIT_Left.Name = "EXIT_Left";
            this.EXIT_Left.Size = new System.Drawing.Size(44, 17);
            this.EXIT_Left.TabIndex = 12;
            this.EXIT_Left.Text = "Left";
            this.EXIT_Left.UseVisualStyleBackColor = true;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(9, 202);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(90, 13);
            this.label4.TabIndex = 11;
            this.label4.Text = "Available Exits";
            // 
            // EXIT_Up
            // 
            this.EXIT_Up.AutoSize = true;
            this.EXIT_Up.Location = new System.Drawing.Point(119, 218);
            this.EXIT_Up.Name = "EXIT_Up";
            this.EXIT_Up.Size = new System.Drawing.Size(40, 17);
            this.EXIT_Up.TabIndex = 14;
            this.EXIT_Up.Text = "Up";
            this.EXIT_Up.UseVisualStyleBackColor = true;
            // 
            // EXIT_Down
            // 
            this.EXIT_Down.AutoSize = true;
            this.EXIT_Down.Location = new System.Drawing.Point(165, 218);
            this.EXIT_Down.Name = "EXIT_Down";
            this.EXIT_Down.Size = new System.Drawing.Size(54, 17);
            this.EXIT_Down.TabIndex = 15;
            this.EXIT_Down.Text = "Down";
            this.EXIT_Down.UseVisualStyleBackColor = true;
            // 
            // browseFile
            // 
            this.browseFile.Location = new System.Drawing.Point(187, 104);
            this.browseFile.Name = "browseFile";
            this.browseFile.Size = new System.Drawing.Size(74, 20);
            this.browseFile.TabIndex = 16;
            this.browseFile.Text = "Browse";
            this.browseFile.UseVisualStyleBackColor = true;
            this.browseFile.Click += new System.EventHandler(this.button1_Click_1);
            // 
            // tileName
            // 
            this.tileName.Location = new System.Drawing.Point(12, 25);
            this.tileName.Name = "tileName";
            this.tileName.Size = new System.Drawing.Size(249, 20);
            this.tileName.TabIndex = 17;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(12, 9);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(96, 13);
            this.label5.TabIndex = 18;
            this.label5.Text = "Tile Description";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(9, 127);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(65, 13);
            this.label6.TabIndex = 20;
            this.label6.Text = "Tile Width";
            // 
            // tileWidth
            // 
            this.tileWidth.Location = new System.Drawing.Point(12, 143);
            this.tileWidth.Name = "tileWidth";
            this.tileWidth.Size = new System.Drawing.Size(71, 20);
            this.tileWidth.TabIndex = 19;
            // 
            // tileHeight
            // 
            this.tileHeight.Location = new System.Drawing.Point(88, 143);
            this.tileHeight.Name = "tileHeight";
            this.tileHeight.Size = new System.Drawing.Size(71, 20);
            this.tileHeight.TabIndex = 21;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(83, 127);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(69, 13);
            this.label7.TabIndex = 22;
            this.label7.Text = "Tile Height";
            // 
            // defaultSizes
            // 
            this.defaultSizes.AutoSize = true;
            this.defaultSizes.Location = new System.Drawing.Point(165, 145);
            this.defaultSizes.Name = "defaultSizes";
            this.defaultSizes.Size = new System.Drawing.Size(106, 17);
            this.defaultSizes.TabIndex = 23;
            this.defaultSizes.Text = "Use default sizes";
            this.defaultSizes.UseVisualStyleBackColor = true;
            this.defaultSizes.CheckedChanged += new System.EventHandler(this.defaultSizes_CheckedChanged);
            // 
            // TileEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(273, 276);
            this.Controls.Add(this.defaultSizes);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.tileHeight);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.tileWidth);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.tileName);
            this.Controls.Add(this.browseFile);
            this.Controls.Add(this.EXIT_Down);
            this.Controls.Add(this.EXIT_Up);
            this.Controls.Add(this.EXIT_Right);
            this.Controls.Add(this.EXIT_Left);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.POI_Door);
            this.Controls.Add(this.POI_Computer);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.tileSet);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.tileSprite);
            this.Controls.Add(this.addTile);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "TileEditor";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Add New Tile...";
            this.Load += new System.EventHandler(this.TileEditor_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button addTile;
        private System.Windows.Forms.TextBox tileSprite;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ComboBox tileSet;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.CheckBox POI_Computer;
        private System.Windows.Forms.CheckBox POI_Door;
        private System.Windows.Forms.CheckBox EXIT_Right;
        private System.Windows.Forms.CheckBox EXIT_Left;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.CheckBox EXIT_Up;
        private System.Windows.Forms.CheckBox EXIT_Down;
        private System.Windows.Forms.Button browseFile;
        private System.Windows.Forms.TextBox tileName;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox tileWidth;
        private System.Windows.Forms.TextBox tileHeight;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.CheckBox defaultSizes;
    }
}