namespace PO_MapMaker
{
    partial class MapList
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
            this.label1 = new System.Windows.Forms.Label();
            this.deleteMap = new System.Windows.Forms.Button();
            this.newMap = new System.Windows.Forms.Button();
            this.editMap = new System.Windows.Forms.Button();
            this.listMapSets = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(12, 8);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(37, 13);
            this.label1.TabIndex = 18;
            this.label1.Text = "Maps";
            // 
            // deleteMap
            // 
            this.deleteMap.Location = new System.Drawing.Point(207, 210);
            this.deleteMap.Name = "deleteMap";
            this.deleteMap.Size = new System.Drawing.Size(75, 23);
            this.deleteMap.TabIndex = 17;
            this.deleteMap.Text = "DELETE";
            this.deleteMap.UseVisualStyleBackColor = true;
            this.deleteMap.Click += new System.EventHandler(this.deleteMap_Click);
            // 
            // newMap
            // 
            this.newMap.Location = new System.Drawing.Point(207, 181);
            this.newMap.Name = "newMap";
            this.newMap.Size = new System.Drawing.Size(75, 23);
            this.newMap.TabIndex = 16;
            this.newMap.Text = "NEW";
            this.newMap.UseVisualStyleBackColor = true;
            this.newMap.Click += new System.EventHandler(this.newMap_Click);
            // 
            // editMap
            // 
            this.editMap.Location = new System.Drawing.Point(207, 239);
            this.editMap.Name = "editMap";
            this.editMap.Size = new System.Drawing.Size(75, 23);
            this.editMap.TabIndex = 15;
            this.editMap.Text = "EDIT";
            this.editMap.UseVisualStyleBackColor = true;
            this.editMap.Click += new System.EventHandler(this.editMap_Click);
            // 
            // listMapSets
            // 
            this.listMapSets.FormattingEnabled = true;
            this.listMapSets.Location = new System.Drawing.Point(15, 24);
            this.listMapSets.Name = "listMapSets";
            this.listMapSets.Size = new System.Drawing.Size(186, 238);
            this.listMapSets.TabIndex = 14;
            // 
            // MapList
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(295, 271);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.deleteMap);
            this.Controls.Add(this.newMap);
            this.Controls.Add(this.editMap);
            this.Controls.Add(this.listMapSets);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "MapList";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Map Editor";
            this.Load += new System.EventHandler(this.MapList_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button deleteMap;
        private System.Windows.Forms.Button newMap;
        private System.Windows.Forms.Button editMap;
        private System.Windows.Forms.ListBox listMapSets;
    }
}