﻿namespace PO_Launcher
{
    partial class PO_Launcher
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
            this.resolutionSelector = new System.Windows.Forms.ComboBox();
            this.label1 = new System.Windows.Forms.Label();
            this.launcherImage = new System.Windows.Forms.PictureBox();
            this.launcherTabs = new System.Windows.Forms.TabControl();
            this.tabPage1 = new System.Windows.Forms.TabPage();
            this.tabPage2 = new System.Windows.Forms.TabPage();
            this.playButton = new System.Windows.Forms.Button();
            this.quitButton = new System.Windows.Forms.Button();
            this.keyBinds = new System.Windows.Forms.ListView();
            this.controlName = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.primaryBind = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            ((System.ComponentModel.ISupportInitialize)(this.launcherImage)).BeginInit();
            this.launcherTabs.SuspendLayout();
            this.tabPage1.SuspendLayout();
            this.tabPage2.SuspendLayout();
            this.SuspendLayout();
            // 
            // resolutionSelector
            // 
            this.resolutionSelector.DropDownStyle = System.Windows.Forms.ComboBoxStyle.DropDownList;
            this.resolutionSelector.FormattingEnabled = true;
            this.resolutionSelector.Items.AddRange(new object[] {
            "2560x1440",
            "1920x1080",
            "1280x720",
            "1024x576",
            "768x432"});
            this.resolutionSelector.Location = new System.Drawing.Point(137, 74);
            this.resolutionSelector.Name = "resolutionSelector";
            this.resolutionSelector.Size = new System.Drawing.Size(154, 21);
            this.resolutionSelector.TabIndex = 0;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(42, 77);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(89, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Screen resolution";
            // 
            // launcherImage
            // 
            this.launcherImage.Location = new System.Drawing.Point(12, 12);
            this.launcherImage.Name = "launcherImage";
            this.launcherImage.Size = new System.Drawing.Size(432, 163);
            this.launcherImage.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.launcherImage.TabIndex = 2;
            this.launcherImage.TabStop = false;
            // 
            // launcherTabs
            // 
            this.launcherTabs.Controls.Add(this.tabPage1);
            this.launcherTabs.Controls.Add(this.tabPage2);
            this.launcherTabs.Location = new System.Drawing.Point(12, 181);
            this.launcherTabs.Name = "launcherTabs";
            this.launcherTabs.SelectedIndex = 0;
            this.launcherTabs.Size = new System.Drawing.Size(436, 204);
            this.launcherTabs.TabIndex = 4;
            // 
            // tabPage1
            // 
            this.tabPage1.Controls.Add(this.label1);
            this.tabPage1.Controls.Add(this.resolutionSelector);
            this.tabPage1.Location = new System.Drawing.Point(4, 22);
            this.tabPage1.Name = "tabPage1";
            this.tabPage1.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage1.Size = new System.Drawing.Size(428, 178);
            this.tabPage1.TabIndex = 0;
            this.tabPage1.Text = "Graphics";
            this.tabPage1.UseVisualStyleBackColor = true;
            // 
            // tabPage2
            // 
            this.tabPage2.Controls.Add(this.keyBinds);
            this.tabPage2.Location = new System.Drawing.Point(4, 22);
            this.tabPage2.Name = "tabPage2";
            this.tabPage2.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage2.Size = new System.Drawing.Size(428, 178);
            this.tabPage2.TabIndex = 1;
            this.tabPage2.Text = "Input";
            this.tabPage2.UseVisualStyleBackColor = true;
            // 
            // playButton
            // 
            this.playButton.Location = new System.Drawing.Point(290, 391);
            this.playButton.Name = "playButton";
            this.playButton.Size = new System.Drawing.Size(75, 23);
            this.playButton.TabIndex = 5;
            this.playButton.Text = "Play!";
            this.playButton.UseVisualStyleBackColor = true;
            this.playButton.Click += new System.EventHandler(this.playButton_Click);
            // 
            // quitButton
            // 
            this.quitButton.Location = new System.Drawing.Point(371, 391);
            this.quitButton.Name = "quitButton";
            this.quitButton.Size = new System.Drawing.Size(75, 23);
            this.quitButton.TabIndex = 6;
            this.quitButton.Text = "Quit";
            this.quitButton.UseVisualStyleBackColor = true;
            this.quitButton.Click += new System.EventHandler(this.quitButton_Click);
            // 
            // keyBinds
            // 
            this.keyBinds.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.controlName,
            this.primaryBind});
            this.keyBinds.FullRowSelect = true;
            this.keyBinds.GridLines = true;
            this.keyBinds.Location = new System.Drawing.Point(6, 6);
            this.keyBinds.Name = "keyBinds";
            this.keyBinds.Size = new System.Drawing.Size(416, 169);
            this.keyBinds.TabIndex = 0;
            this.keyBinds.UseCompatibleStateImageBehavior = false;
            this.keyBinds.View = System.Windows.Forms.View.Details;
            // 
            // controlName
            // 
            this.controlName.Text = "Control";
            this.controlName.Width = 200;
            // 
            // primaryBind
            // 
            this.primaryBind.Text = "Primary";
            this.primaryBind.Width = 200;
            // 
            // PO_Launcher
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(456, 423);
            this.Controls.Add(this.quitButton);
            this.Controls.Add(this.playButton);
            this.Controls.Add(this.launcherTabs);
            this.Controls.Add(this.launcherImage);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "PO_Launcher";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Planned Obsolescence Launcher";
            this.Load += new System.EventHandler(this.PO_Launcher_Load);
            ((System.ComponentModel.ISupportInitialize)(this.launcherImage)).EndInit();
            this.launcherTabs.ResumeLayout(false);
            this.tabPage1.ResumeLayout(false);
            this.tabPage1.PerformLayout();
            this.tabPage2.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.ComboBox resolutionSelector;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.PictureBox launcherImage;
        private System.Windows.Forms.TabControl launcherTabs;
        private System.Windows.Forms.TabPage tabPage1;
        private System.Windows.Forms.TabPage tabPage2;
        private System.Windows.Forms.Button playButton;
        private System.Windows.Forms.Button quitButton;
        private System.Windows.Forms.ListView keyBinds;
        private System.Windows.Forms.ColumnHeader controlName;
        private System.Windows.Forms.ColumnHeader primaryBind;
    }
}

