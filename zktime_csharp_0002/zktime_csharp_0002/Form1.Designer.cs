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
            this.lblMessage = new System.Windows.Forms.RichTextBox();
            this.radioV1N = new System.Windows.Forms.RadioButton();
            this.btnBeep = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.radioRegister = new System.Windows.Forms.RadioButton();
            this.radioV1_1 = new System.Windows.Forms.RadioButton();
            this.btRed = new System.Windows.Forms.Button();
            this.btGreen = new System.Windows.Forms.Button();
            this.panel2 = new System.Windows.Forms.Panel();
            this.radioThumb = new System.Windows.Forms.RadioButton();
            this.radioIndex = new System.Windows.Forms.RadioButton();
            ((System.ComponentModel.ISupportInitialize)(this.fingerPrintBox)).BeginInit();
            this.panel1.SuspendLayout();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // btConnect
            // 
            this.btConnect.Location = new System.Drawing.Point(12, 450);
            this.btConnect.Name = "btConnect";
            this.btConnect.Size = new System.Drawing.Size(75, 23);
            this.btConnect.TabIndex = 0;
            this.btConnect.Text = "Connect";
            this.btConnect.UseVisualStyleBackColor = true;
            this.btConnect.Click += new System.EventHandler(this.btConnect_Click);
            // 
            // btnDisconnect
            // 
            this.btnDisconnect.Enabled = false;
            this.btnDisconnect.Location = new System.Drawing.Point(12, 485);
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
            this.fingerPrintBox.Location = new System.Drawing.Point(-1, 12);
            this.fingerPrintBox.Name = "fingerPrintBox";
            this.fingerPrintBox.Size = new System.Drawing.Size(321, 416);
            this.fingerPrintBox.TabIndex = 5;
            this.fingerPrintBox.TabStop = false;
            // 
            // lblMessage
            // 
            this.lblMessage.Location = new System.Drawing.Point(326, 12);
            this.lblMessage.Name = "lblMessage";
            this.lblMessage.Size = new System.Drawing.Size(231, 366);
            this.lblMessage.TabIndex = 10;
            this.lblMessage.Text = "";
            // 
            // radioV1N
            // 
            this.radioV1N.AutoSize = true;
            this.radioV1N.Checked = true;
            this.radioV1N.Location = new System.Drawing.Point(15, 19);
            this.radioV1N.Name = "radioV1N";
            this.radioV1N.Size = new System.Drawing.Size(73, 17);
            this.radioV1N.TabIndex = 11;
            this.radioV1N.TabStop = true;
            this.radioV1N.Text = "verify(1,N)";
            this.radioV1N.UseVisualStyleBackColor = true;
            this.radioV1N.CheckedChanged += new System.EventHandler(this.radioV1N_CheckedChanged);
            // 
            // btnBeep
            // 
            this.btnBeep.Location = new System.Drawing.Point(219, 488);
            this.btnBeep.Name = "btnBeep";
            this.btnBeep.Size = new System.Drawing.Size(75, 23);
            this.btnBeep.TabIndex = 12;
            this.btnBeep.Text = "Beep";
            this.btnBeep.UseVisualStyleBackColor = true;
            this.btnBeep.Click += new System.EventHandler(this.btnBeep_Click);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.radioRegister);
            this.panel1.Controls.Add(this.radioV1_1);
            this.panel1.Controls.Add(this.radioV1N);
            this.panel1.Location = new System.Drawing.Point(436, 408);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(121, 100);
            this.panel1.TabIndex = 14;
            // 
            // radioRegister
            // 
            this.radioRegister.AutoSize = true;
            this.radioRegister.Location = new System.Drawing.Point(15, 66);
            this.radioRegister.Name = "radioRegister";
            this.radioRegister.Size = new System.Drawing.Size(59, 17);
            this.radioRegister.TabIndex = 13;
            this.radioRegister.TabStop = true;
            this.radioRegister.Text = "register";
            this.radioRegister.UseVisualStyleBackColor = true;
            this.radioRegister.CheckedChanged += new System.EventHandler(this.btRegister_CheckedChanged);
            // 
            // radioV1_1
            // 
            this.radioV1_1.AutoSize = true;
            this.radioV1_1.Location = new System.Drawing.Point(15, 42);
            this.radioV1_1.Name = "radioV1_1";
            this.radioV1_1.Size = new System.Drawing.Size(71, 17);
            this.radioV1_1.TabIndex = 12;
            this.radioV1_1.TabStop = true;
            this.radioV1_1.Text = "verify(1,1)";
            this.radioV1_1.UseVisualStyleBackColor = true;
            this.radioV1_1.CheckedChanged += new System.EventHandler(this.radioButton1_CheckedChanged);
            // 
            // btRed
            // 
            this.btRed.Location = new System.Drawing.Point(129, 485);
            this.btRed.Name = "btRed";
            this.btRed.Size = new System.Drawing.Size(75, 23);
            this.btRed.TabIndex = 15;
            this.btRed.Text = "Red";
            this.btRed.UseVisualStyleBackColor = true;
            this.btRed.Click += new System.EventHandler(this.btRed_Click);
            // 
            // btGreen
            // 
            this.btGreen.Location = new System.Drawing.Point(129, 450);
            this.btGreen.Name = "btGreen";
            this.btGreen.Size = new System.Drawing.Size(75, 23);
            this.btGreen.TabIndex = 16;
            this.btGreen.Text = "Green";
            this.btGreen.UseVisualStyleBackColor = true;
            this.btGreen.Click += new System.EventHandler(this.btGreen_Click);
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.radioIndex);
            this.panel2.Controls.Add(this.radioThumb);
            this.panel2.Enabled = false;
            this.panel2.Location = new System.Drawing.Point(299, 427);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(121, 59);
            this.panel2.TabIndex = 14;
            // 
            // radioThumb
            // 
            this.radioThumb.AutoSize = true;
            this.radioThumb.Checked = true;
            this.radioThumb.Location = new System.Drawing.Point(10, 13);
            this.radioThumb.Name = "radioThumb";
            this.radioThumb.Size = new System.Drawing.Size(58, 17);
            this.radioThumb.TabIndex = 0;
            this.radioThumb.TabStop = true;
            this.radioThumb.Text = "Thumb";
            this.radioThumb.UseVisualStyleBackColor = true;
            // 
            // radioIndex
            // 
            this.radioIndex.AutoSize = true;
            this.radioIndex.Location = new System.Drawing.Point(10, 36);
            this.radioIndex.Name = "radioIndex";
            this.radioIndex.Size = new System.Drawing.Size(51, 17);
            this.radioIndex.TabIndex = 1;
            this.radioIndex.Text = "Index";
            this.radioIndex.UseVisualStyleBackColor = true;
            // 
            // mainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(569, 523);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.btGreen);
            this.Controls.Add(this.btRed);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.btnBeep);
            this.Controls.Add(this.lblMessage);
            this.Controls.Add(this.fingerPrintBox);
            this.Controls.Add(this.btnDisconnect);
            this.Controls.Add(this.btConnect);
            this.Name = "mainForm";
            this.Text = "MainForm";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            ((System.ComponentModel.ISupportInitialize)(this.fingerPrintBox)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button btConnect;
        private System.Windows.Forms.Button btnDisconnect;
        private System.Windows.Forms.PictureBox fingerPrintBox;
        private System.Windows.Forms.RichTextBox lblMessage;
        private System.Windows.Forms.RadioButton radioV1N;
        private System.Windows.Forms.Button btnBeep;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.RadioButton radioRegister;
        private System.Windows.Forms.RadioButton radioV1_1;
        private System.Windows.Forms.Button btRed;
        private System.Windows.Forms.Button btGreen;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.RadioButton radioIndex;
        private System.Windows.Forms.RadioButton radioThumb;
    }
}

