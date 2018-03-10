namespace zktime_csharp_0002
{
    partial class mainForm
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
            this.btConnect = new System.Windows.Forms.Button();
            this.btnDisconnect = new System.Windows.Forms.Button();
            this.fingerPrintBox = new System.Windows.Forms.PictureBox();
            this.btnRegister = new System.Windows.Forms.Button();
            this.btnSaveImage = new System.Windows.Forms.Button();
            this.btnVerify1_1 = new System.Windows.Forms.Button();
            this.btnVerify1_N = new System.Windows.Forms.Button();
            this.lblMessage = new System.Windows.Forms.RichTextBox();
            ((System.ComponentModel.ISupportInitialize)(this.fingerPrintBox)).BeginInit();
            this.SuspendLayout();
            // 
            // btConnect
            // 
            this.btConnect.Location = new System.Drawing.Point(48, 332);
            this.btConnect.Name = "btConnect";
            this.btConnect.Size = new System.Drawing.Size(75, 23);
            this.btConnect.TabIndex = 0;
            this.btConnect.Text = "Connect";
            this.btConnect.UseVisualStyleBackColor = true;
            this.btConnect.Click += new System.EventHandler(this.btConnect_Click);
            // 
            // btnDisconnect
            // 
            this.btnDisconnect.Location = new System.Drawing.Point(146, 390);
            this.btnDisconnect.Name = "btnDisconnect";
            this.btnDisconnect.Size = new System.Drawing.Size(75, 23);
            this.btnDisconnect.TabIndex = 1;
            this.btnDisconnect.Text = "Disconnect";
            this.btnDisconnect.UseVisualStyleBackColor = true;
            this.btnDisconnect.Click += new System.EventHandler(this.btnDisconnect_Click);
            // 
            // fingerPrintBox
            // 
            this.fingerPrintBox.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.fingerPrintBox.Location = new System.Drawing.Point(48, 64);
            this.fingerPrintBox.Name = "fingerPrintBox";
            this.fingerPrintBox.Size = new System.Drawing.Size(233, 240);
            this.fingerPrintBox.TabIndex = 5;
            this.fingerPrintBox.TabStop = false;
            // 
            // btnRegister
            // 
            this.btnRegister.Location = new System.Drawing.Point(146, 332);
            this.btnRegister.Name = "btnRegister";
            this.btnRegister.Size = new System.Drawing.Size(75, 23);
            this.btnRegister.TabIndex = 6;
            this.btnRegister.Text = "Register";
            this.btnRegister.UseVisualStyleBackColor = true;
            this.btnRegister.Click += new System.EventHandler(this.btnRegister_Click);
            // 
            // btnSaveImage
            // 
            this.btnSaveImage.Location = new System.Drawing.Point(48, 361);
            this.btnSaveImage.Name = "btnSaveImage";
            this.btnSaveImage.Size = new System.Drawing.Size(75, 23);
            this.btnSaveImage.TabIndex = 7;
            this.btnSaveImage.Text = "Save Image";
            this.btnSaveImage.UseVisualStyleBackColor = true;
            // 
            // btnVerify1_1
            // 
            this.btnVerify1_1.Location = new System.Drawing.Point(48, 390);
            this.btnVerify1_1.Name = "btnVerify1_1";
            this.btnVerify1_1.Size = new System.Drawing.Size(75, 23);
            this.btnVerify1_1.TabIndex = 8;
            this.btnVerify1_1.Text = "Verify (1,1)";
            this.btnVerify1_1.UseVisualStyleBackColor = true;
            // 
            // btnVerify1_N
            // 
            this.btnVerify1_N.Location = new System.Drawing.Point(146, 361);
            this.btnVerify1_N.Name = "btnVerify1_N";
            this.btnVerify1_N.Size = new System.Drawing.Size(75, 23);
            this.btnVerify1_N.TabIndex = 9;
            this.btnVerify1_N.Text = "Verify(1,N)";
            this.btnVerify1_N.UseVisualStyleBackColor = true;
            this.btnVerify1_N.Click += new System.EventHandler(this.btnIdentify1N_Click);
            // 
            // lblMessage
            // 
            this.lblMessage.Location = new System.Drawing.Point(326, 41);
            this.lblMessage.Name = "lblMessage";
            this.lblMessage.Size = new System.Drawing.Size(231, 517);
            this.lblMessage.TabIndex = 10;
            this.lblMessage.Text = "";
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(569, 570);
            this.Controls.Add(this.lblMessage);
            this.Controls.Add(this.btnVerify1_N);
            this.Controls.Add(this.btnVerify1_1);
            this.Controls.Add(this.btnSaveImage);
            this.Controls.Add(this.btnRegister);
            this.Controls.Add(this.fingerPrintBox);
            this.Controls.Add(this.btnDisconnect);
            this.Controls.Add(this.btConnect);
            this.Name = "mainForm";
            this.Text = "MainForm";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            ((System.ComponentModel.ISupportInitialize)(this.fingerPrintBox)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btConnect;
        private System.Windows.Forms.Button btnDisconnect;
        private System.Windows.Forms.PictureBox fingerPrintBox;
        private System.Windows.Forms.Button btnRegister;
        private System.Windows.Forms.Button btnSaveImage;
        private System.Windows.Forms.Button btnVerify1_1;
        private System.Windows.Forms.Button btnVerify1_N;
        private System.Windows.Forms.RichTextBox lblMessage;
    }
}

