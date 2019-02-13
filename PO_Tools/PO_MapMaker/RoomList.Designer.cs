namespace PO_MapMaker
{
    partial class RoomList
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
            this.deleteRoom = new System.Windows.Forms.Button();
            this.newRoom = new System.Windows.Forms.Button();
            this.editRoom = new System.Windows.Forms.Button();
            this.listRooms = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(12, 9);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(45, 13);
            this.label1.TabIndex = 13;
            this.label1.Text = "Rooms";
            // 
            // deleteRoom
            // 
            this.deleteRoom.Location = new System.Drawing.Point(207, 211);
            this.deleteRoom.Name = "deleteRoom";
            this.deleteRoom.Size = new System.Drawing.Size(75, 23);
            this.deleteRoom.TabIndex = 12;
            this.deleteRoom.Text = "DELETE";
            this.deleteRoom.UseVisualStyleBackColor = true;
            this.deleteRoom.Click += new System.EventHandler(this.deleteRoom_Click);
            // 
            // newRoom
            // 
            this.newRoom.Location = new System.Drawing.Point(207, 182);
            this.newRoom.Name = "newRoom";
            this.newRoom.Size = new System.Drawing.Size(75, 23);
            this.newRoom.TabIndex = 11;
            this.newRoom.Text = "NEW";
            this.newRoom.UseVisualStyleBackColor = true;
            this.newRoom.Click += new System.EventHandler(this.newRoom_Click);
            // 
            // editRoom
            // 
            this.editRoom.Location = new System.Drawing.Point(207, 240);
            this.editRoom.Name = "editRoom";
            this.editRoom.Size = new System.Drawing.Size(75, 23);
            this.editRoom.TabIndex = 10;
            this.editRoom.Text = "EDIT";
            this.editRoom.UseVisualStyleBackColor = true;
            this.editRoom.Click += new System.EventHandler(this.editRoom_Click);
            // 
            // listRooms
            // 
            this.listRooms.FormattingEnabled = true;
            this.listRooms.Location = new System.Drawing.Point(15, 25);
            this.listRooms.Name = "listRooms";
            this.listRooms.Size = new System.Drawing.Size(186, 238);
            this.listRooms.TabIndex = 9;
            // 
            // RoomList
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(295, 271);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.deleteRoom);
            this.Controls.Add(this.newRoom);
            this.Controls.Add(this.editRoom);
            this.Controls.Add(this.listRooms);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.Name = "RoomList";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Room Editor";
            this.Load += new System.EventHandler(this.RoomList_Load);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button deleteRoom;
        private System.Windows.Forms.Button newRoom;
        private System.Windows.Forms.Button editRoom;
        private System.Windows.Forms.ListBox listRooms;
    }
}