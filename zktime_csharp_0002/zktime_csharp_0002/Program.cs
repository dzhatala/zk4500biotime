using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;

namespace zktime_csharp_0002
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        /// 
        //static ZKFPEngXControl.ZKFPEngX  zkeng=new ZKFPEngXControl.ZKFPEngX();
        [STAThread]
        static void Main()
        {
            //zkemkeeper.
            //ZKFPEngXControl.ZKFPEngX zkeng = new ZKFPEngXControl.ZKFPEngX();
            Application.EnableVisualStyles();

            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new mainForm());
        }
    }
}
