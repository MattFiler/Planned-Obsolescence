namespace PO_MapMaker
{
    partial class MapEditor
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
            this.refreshRoom = new System.Windows.Forms.Button();
            this.saveRoom = new System.Windows.Forms.Button();
            this.roomHeight = new System.Windows.Forms.NumericUpDown();
            this.roomWidth = new System.Windows.Forms.NumericUpDown();
            this.defaultSizes = new System.Windows.Forms.CheckBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.roomName = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.roomHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.roomWidth)).BeginInit();
            this.SuspendLayout();
            // 
            // refreshRoom
            // 
            this.refreshRoom.Location = new System.Drawing.Point(12, 92);
            this.refreshRoom.Name = "refreshRoom";
            this.refreshRoom.Size = new System.Drawing.Size(249, 26);
            this.refreshRoom.TabIndex = 48;
            this.refreshRoom.Text = "Refresh";
            this.refreshRoom.UseVisualStyleBackColor = true;
            this.refreshRoom.Click += new System.EventHandler(this.refreshRoom_Click);
            // 
            // saveRoom
            // 
            this.saveRoom.Location = new System.Drawing.Point(12, 208);
            this.saveRoom.Name = "saveRoom";
            this.saveRoom.Size = new System.Drawing.Size(249, 26);
            this.saveRoom.TabIndex = 47;
            this.saveRoom.Text = "Save Room";
            this.saveRoom.UseVisualStyleBackColor = true;
            this.saveRoom.Click += new System.EventHandler(this.saveRoom_Click);
            // 
            // roomHeight
            // 
            this.roomHeight.Location = new System.Drawing.Point(89, 66);
            this.roomHeight.Name = "roomHeight";
            this.roomHeight.Size = new System.Drawing.Size(71, 20);
            this.roomHeight.TabIndex = 46;
            // 
            // roomWidth
            // 
            this.roomWidth.Location = new System.Drawing.Point(12, 66);
            this.roomWidth.Name = "roomWidth";
            this.roomWidth.Size = new System.Drawing.Size(71, 20);
            this.roomWidth.TabIndex = 45;
            // 
            // defaultSizes
            // 
            this.defaultSizes.AutoSize = true;
            this.defaultSizes.Checked = true;
            this.defaultSizes.CheckState = System.Windows.Forms.CheckState.Checked;
            this.defaultSizes.Location = new System.Drawing.Point(165, 68);
            this.defaultSizes.Name = "defaultSizes";
            this.defaultSizes.Size = new System.Drawing.Size(106, 17);
            this.defaultSizes.TabIndex = 44;
            this.defaultSizes.Text = "Use default sizes";
            this.defaultSizes.UseVisualStyleBackColor = true;
            this.defaultSizes.CheckedChanged += new System.EventHandler(this.defaultSizes_CheckedChanged);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(85, 50);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(44, 13);
            this.label7.TabIndex = 43;
            this.label7.Text = "Height";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(10, 50);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(40, 13);
            this.label6.TabIndex = 42;
            this.label6.Text = "Width";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(9, 9);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(99, 13);
            this.label5.TabIndex = 41;
            this.label5.Text = "Map Description";
            // 
            // roomName
            // 
            this.roomName.Location = new System.Drawing.Point(12, 25);
            this.roomName.Name = "roomName";
            this.roomName.Size = new System.Drawing.Size(249, 20);
            this.roomName.TabIndex = 40;
            // 
            // MapEditor
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
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "MapEditor";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Map Editor";
            this.Load += new System.EventHandler(this.MapEditor_Load_1);
            ((System.ComponentModel.ISupportInitialize)(this.roomHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.roomWidth)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button refreshRoom;
        private System.Windows.Forms.Button saveRoom;
        private System.Windows.Forms.NumericUpDown roomHeight;
        private System.Windows.Forms.NumericUpDown roomWidth;
        private System.Windows.Forms.CheckBox defaultSizes;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox roomName;
    }
}