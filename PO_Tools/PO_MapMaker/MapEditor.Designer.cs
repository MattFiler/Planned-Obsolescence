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
            this.refreshMap = new System.Windows.Forms.Button();
            this.saveMap = new System.Windows.Forms.Button();
            this.mapHeight = new System.Windows.Forms.NumericUpDown();
            this.mapWidth = new System.Windows.Forms.NumericUpDown();
            this.defaultSizes = new System.Windows.Forms.CheckBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.mapDescription = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.mapHeight)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.mapWidth)).BeginInit();
            this.SuspendLayout();
            // 
            // refreshMap
            // 
            this.refreshMap.Location = new System.Drawing.Point(12, 92);
            this.refreshMap.Name = "refreshMap";
            this.refreshMap.Size = new System.Drawing.Size(249, 26);
            this.refreshMap.TabIndex = 48;
            this.refreshMap.Text = "Refresh";
            this.refreshMap.UseVisualStyleBackColor = true;
            this.refreshMap.Click += new System.EventHandler(this.refreshRoom_Click);
            // 
            // saveMap
            // 
            this.saveMap.Location = new System.Drawing.Point(12, 208);
            this.saveMap.Name = "saveMap";
            this.saveMap.Size = new System.Drawing.Size(249, 26);
            this.saveMap.TabIndex = 47;
            this.saveMap.Text = "Save Map";
            this.saveMap.UseVisualStyleBackColor = true;
            this.saveMap.Click += new System.EventHandler(this.saveRoom_Click);
            // 
            // mapHeight
            // 
            this.mapHeight.Location = new System.Drawing.Point(89, 66);
            this.mapHeight.Name = "mapHeight";
            this.mapHeight.Size = new System.Drawing.Size(71, 20);
            this.mapHeight.TabIndex = 46;
            // 
            // mapWidth
            // 
            this.mapWidth.Location = new System.Drawing.Point(12, 66);
            this.mapWidth.Name = "mapWidth";
            this.mapWidth.Size = new System.Drawing.Size(71, 20);
            this.mapWidth.TabIndex = 45;
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
            // mapDescription
            // 
            this.mapDescription.Location = new System.Drawing.Point(12, 25);
            this.mapDescription.Name = "mapDescription";
            this.mapDescription.Size = new System.Drawing.Size(249, 20);
            this.mapDescription.TabIndex = 40;
            // 
            // MapEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(273, 245);
            this.Controls.Add(this.refreshMap);
            this.Controls.Add(this.saveMap);
            this.Controls.Add(this.mapHeight);
            this.Controls.Add(this.mapWidth);
            this.Controls.Add(this.defaultSizes);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.mapDescription);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "MapEditor";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Map Editor";
            this.Load += new System.EventHandler(this.MapEditor_Load_1);
            ((System.ComponentModel.ISupportInitialize)(this.mapHeight)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.mapWidth)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button refreshMap;
        private System.Windows.Forms.Button saveMap;
        private System.Windows.Forms.NumericUpDown mapHeight;
        private System.Windows.Forms.NumericUpDown mapWidth;
        private System.Windows.Forms.CheckBox defaultSizes;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox mapDescription;
    }
}