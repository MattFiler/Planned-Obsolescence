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
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.roomName = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.tileSet = new System.Windows.Forms.ComboBox();
            this.roomWidth = new System.Windows.Forms.NumericUpDown();
            this.roomHeight = new System.Windows.Forms.NumericUpDown();
            this.saveRoom = new System.Windows.Forms.Button();
            this.refreshRoom = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.roomWidth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.roomHeight)).BeginInit();
            this.SuspendLayout();
            // 
            // defaultSizes
            // 
            this.defaultSizes.AutoSize = true;
            this.defaultSizes.Checked = true;
            this.defaultSizes.CheckState = System.Windows.Forms.CheckState.Checked;
            this.defaultSizes.Location = new System.Drawing.Point(165, 110);
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
            this.label7.Location = new System.Drawing.Point(85, 92);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(44, 13);
            this.label7.TabIndex = 31;
            this.label7.Text = "Height";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(10, 92);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(40, 13);
            this.label6.TabIndex = 29;
            this.label6.Text = "Width";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(9, 9);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(107, 13);
            this.label5.TabIndex = 27;
            this.label5.Text = "Room Description";
            // 
            // roomName
            // 
            this.roomName.Location = new System.Drawing.Point(12, 25);
            this.roomName.Name = "roomName";
            this.roomName.Size = new System.Drawing.Size(249, 20);
            this.roomName.TabIndex = 26;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(9, 49);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(51, 13);
            this.label2.TabIndex = 25;
            this.label2.Text = "Tile Set";
            // 
            // tileSet
            // 
            this.tileSet.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.tileSet.FormattingEnabled = true;
            this.tileSet.Location = new System.Drawing.Point(12, 65);
            this.tileSet.Name = "tileSet";
            this.tileSet.Size = new System.Drawing.Size(249, 21);
            this.tileSet.TabIndex = 24;
            this.tileSet.SelectedIndexChanged += new System.EventHandler(this.tileSet_SelectedIndexChanged);
            // 
            // roomWidth
            // 
            this.roomWidth.Location = new System.Drawing.Point(12, 108);
            this.roomWidth.Name = "roomWidth";
            this.roomWidth.Size = new System.Drawing.Size(71, 20);
            this.roomWidth.TabIndex = 34;
            this.roomWidth.ValueChanged += new System.EventHandler(this.roomWidth_ValueChanged);
            // 
            // roomHeight
            // 
            this.roomHeight.Location = new System.Drawing.Point(89, 108);
            this.roomHeight.Name = "roomHeight";
            this.roomHeight.Size = new System.Drawing.Size(71, 20);
            this.roomHeight.TabIndex = 35;
            this.roomHeight.ValueChanged += new System.EventHandler(this.roomHeight_ValueChanged);
            // 
            // saveRoom
            // 
            this.saveRoom.Location = new System.Drawing.Point(12, 208);
            this.saveRoom.Name = "saveRoom";
            this.saveRoom.Size = new System.Drawing.Size(249, 26);
            this.saveRoom.TabIndex = 36;
            this.saveRoom.Text = "Save Room";
            this.saveRoom.UseVisualStyleBackColor = true;
            this.saveRoom.Click += new System.EventHandler(this.saveRoom_Click);
            // 
            // refreshRoom
            // 
            this.refreshRoom.Location = new System.Drawing.Point(12, 134);
            this.refreshRoom.Name = "refreshRoom";
            this.refreshRoom.Size = new System.Drawing.Size(249, 26);
            this.refreshRoom.TabIndex = 37;
            this.refreshRoom.Text = "Refresh";
            this.refreshRoom.UseVisualStyleBackColor = true;
            this.refreshRoom.Click += new System.EventHandler(this.refreshRoom_Click);
            // 
            // RoomEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(273, 245);
            this.Controls.Add(this.refreshRoom);
            this.Controls.Add(this.saveRoom);
            this.Controls.Add(this.roomHeight);
            this.Controls.Add(this.roomWidth);
            this.Controls.Add(this.defaultSizes);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.roomName);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.tileSet);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "RoomEditor";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Room Editor";
            this.Load += new System.EventHandler(this.RoomEditor_Load);
            ((System.ComponentModel.ISupportInitialize)(this.roomWidth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.roomHeight)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.CheckBox defaultSizes;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox roomName;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox tileSet;
        private System.Windows.Forms.NumericUpDown roomWidth;
        private System.Windows.Forms.NumericUpDown roomHeight;
        private System.Windows.Forms.Button saveRoom;
        private System.Windows.Forms.Button refreshRoom;
    }
}