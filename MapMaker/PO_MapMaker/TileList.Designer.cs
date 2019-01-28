namespace PO_MapMaker
{
    partial class TileList
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
            this.listTileSet = new System.Windows.Forms.ListBox();
            this.listTile = new System.Windows.Forms.ListBox();
            this.loadSpriteSet = new System.Windows.Forms.Button();
            this.newTileSet = new System.Windows.Forms.Button();
            this.deleteTileSet = new System.Windows.Forms.Button();
            this.deleteTile = new System.Windows.Forms.Button();
            this.newTile = new System.Windows.Forms.Button();
            this.editTile = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // listTileSet
            // 
            this.listTileSet.FormattingEnabled = true;
            this.listTileSet.Location = new System.Drawing.Point(12, 26);
            this.listTileSet.Name = "listTileSet";
            this.listTileSet.Size = new System.Drawing.Size(200, 225);
            this.listTileSet.TabIndex = 0;
            // 
            // listTile
            // 
            this.listTile.FormattingEnabled = true;
            this.listTile.Location = new System.Drawing.Point(299, 26);
            this.listTile.Name = "listTile";
            this.listTile.Size = new System.Drawing.Size(601, 225);
            this.listTile.TabIndex = 1;
            // 
            // loadSpriteSet
            // 
            this.loadSpriteSet.Location = new System.Drawing.Point(218, 106);
            this.loadSpriteSet.Name = "loadSpriteSet";
            this.loadSpriteSet.Size = new System.Drawing.Size(75, 65);
            this.loadSpriteSet.TabIndex = 2;
            this.loadSpriteSet.Text = "OPEN >>";
            this.loadSpriteSet.UseVisualStyleBackColor = true;
            this.loadSpriteSet.Click += new System.EventHandler(this.loadSpriteSet_Click);
            // 
            // newTileSet
            // 
            this.newTileSet.Location = new System.Drawing.Point(12, 257);
            this.newTileSet.Name = "newTileSet";
            this.newTileSet.Size = new System.Drawing.Size(75, 23);
            this.newTileSet.TabIndex = 3;
            this.newTileSet.Text = "NEW";
            this.newTileSet.UseVisualStyleBackColor = true;
            this.newTileSet.Click += new System.EventHandler(this.newTileSet_Click);
            // 
            // deleteTileSet
            // 
            this.deleteTileSet.Location = new System.Drawing.Point(93, 257);
            this.deleteTileSet.Name = "deleteTileSet";
            this.deleteTileSet.Size = new System.Drawing.Size(75, 23);
            this.deleteTileSet.TabIndex = 4;
            this.deleteTileSet.Text = "DELETE";
            this.deleteTileSet.UseVisualStyleBackColor = true;
            this.deleteTileSet.Click += new System.EventHandler(this.deleteTileSet_Click);
            // 
            // deleteTile
            // 
            this.deleteTile.Location = new System.Drawing.Point(380, 257);
            this.deleteTile.Name = "deleteTile";
            this.deleteTile.Size = new System.Drawing.Size(75, 23);
            this.deleteTile.TabIndex = 6;
            this.deleteTile.Text = "DELETE";
            this.deleteTile.UseVisualStyleBackColor = true;
            this.deleteTile.Click += new System.EventHandler(this.deleteTile_Click);
            // 
            // newTile
            // 
            this.newTile.Location = new System.Drawing.Point(299, 257);
            this.newTile.Name = "newTile";
            this.newTile.Size = new System.Drawing.Size(75, 23);
            this.newTile.TabIndex = 5;
            this.newTile.Text = "NEW";
            this.newTile.UseVisualStyleBackColor = true;
            this.newTile.Click += new System.EventHandler(this.newTile_Click);
            // 
            // editTile
            // 
            this.editTile.Location = new System.Drawing.Point(461, 257);
            this.editTile.Name = "editTile";
            this.editTile.Size = new System.Drawing.Size(75, 23);
            this.editTile.TabIndex = 7;
            this.editTile.Text = "EDIT";
            this.editTile.UseVisualStyleBackColor = true;
            this.editTile.Click += new System.EventHandler(this.editTile_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(9, 10);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(57, 13);
            this.label1.TabIndex = 8;
            this.label1.Text = "Tile Sets";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(296, 10);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(34, 13);
            this.label2.TabIndex = 9;
            this.label2.Text = "Tiles";
            // 
            // TileList
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(912, 289);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.editTile);
            this.Controls.Add(this.deleteTile);
            this.Controls.Add(this.newTile);
            this.Controls.Add(this.deleteTileSet);
            this.Controls.Add(this.newTileSet);
            this.Controls.Add(this.loadSpriteSet);
            this.Controls.Add(this.listTile);
            this.Controls.Add(this.listTileSet);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "TileList";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Tile Editor";
            this.Load += new System.EventHandler(this.TileList_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox listTileSet;
        private System.Windows.Forms.ListBox listTile;
        private System.Windows.Forms.Button loadSpriteSet;
        private System.Windows.Forms.Button newTileSet;
        private System.Windows.Forms.Button deleteTileSet;
        private System.Windows.Forms.Button deleteTile;
        private System.Windows.Forms.Button newTile;
        private System.Windows.Forms.Button editTile;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}