namespace PO_MapMaker
{
    partial class RoomEditor
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
            this.defaultSizes = new System.Windows.Forms.CheckBox();
            this.label7 = new System.Windows.Forms.Label();
            this.roomHeight = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.roomWidth = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.tileName = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.tileSet = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // defaultSizes
            // 
            this.defaultSizes.AutoSize = true;
            this.defaultSizes.Checked = true;
            this.defaultSizes.CheckState = System.Windows.Forms.CheckState.Checked;
            this.defaultSizes.Location = new System.Drawing.Point(165, 68);
            this.defaultSizes.Name = "defaultSizes";
            this.defaultSizes.Size = new System.Drawing.Size(106, 17);
            this.defaultSizes.TabIndex = 32;
            this.defaultSizes.Text = "Use default sizes";
            this.defaultSizes.UseVisualStyleBackColor = true;
            this.defaultSizes.CheckedChanged += new System.EventHandler(this.defaultSizes_CheckedChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(83, 50);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(69, 13);
            this.label7.TabIndex = 31;
            this.label7.Text = "Tile Height";
            // 
            // roomHeight
            // 
            this.roomHeight.Enabled = false;
            this.roomHeight.Location = new System.Drawing.Point(88, 66);
            this.roomHeight.Name = "roomHeight";
            this.roomHeight.Size = new System.Drawing.Size(71, 20);
            this.roomHeight.TabIndex = 30;
            this.roomHeight.TextChanged += new System.EventHandler(this.roomHeight_TextChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(9, 50);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(65, 13);
            this.label6.TabIndex = 29;
            this.label6.Text = "Tile Width";
            // 
            // roomWidth
            // 
            this.roomWidth.Enabled = false;
            this.roomWidth.Location = new System.Drawing.Point(12, 66);
            this.roomWidth.Name = "roomWidth";
            this.roomWidth.Size = new System.Drawing.Size(71, 20);
            this.roomWidth.TabIndex = 28;
            this.roomWidth.TextChanged += new System.EventHandler(this.roomWidth_TextChanged);
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(12, 9);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(96, 13);
            this.label5.TabIndex = 27;
            this.label5.Text = "Tile Description";
            // 
            // tileName
            // 
            this.tileName.Location = new System.Drawing.Point(12, 25);
            this.tileName.Name = "tileName";
            this.tileName.Size = new System.Drawing.Size(249, 20);
            this.tileName.TabIndex = 26;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(264, 8);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(51, 13);
            this.label2.TabIndex = 25;
            this.label2.Text = "Tile Set";
            // 
            // tileSet
            // 
            this.tileSet.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.tileSet.FormattingEnabled = true;
            this.tileSet.Location = new System.Drawing.Point(267, 24);
            this.tileSet.Name = "tileSet";
            this.tileSet.Size = new System.Drawing.Size(249, 21);
            this.tileSet.TabIndex = 24;
            this.tileSet.SelectedIndexChanged += new System.EventHandler(this.tileSet_SelectedIndexChanged);
            // 
            // RoomEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1243, 795);
            this.Controls.Add(this.defaultSizes);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.roomHeight);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.roomWidth);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.tileName);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.tileSet);
            this.Name = "RoomEditor";
            this.Text = "RoomEditor";
            this.Load += new System.EventHandler(this.RoomEditor_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox defaultSizes;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox roomHeight;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.TextBox roomWidth;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox tileName;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox tileSet;
    }
}