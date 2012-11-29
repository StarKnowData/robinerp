using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using BCST.Common;

namespace Bzw.Inhersits
{
    public partial class VipApply:UiCommon.AppBasePage
    {

       
       
        /// <summary>
        /// form1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlForm form1;

        protected global::System.Web.UI.WebControls.Label lblMsg;
        
        public string bgColor = string.Empty;
        public string PropPrice = string.Empty;
        public string VipDay ="7";
        public int MoneyToViptimeWeek = 0;
        public int MoneyToViptimeMonth = 0;
        public int MoneyToViptimeHYear = 0;
        public int MoneyToViptimeYear = 0;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
             
                bgColor = CommonManager.Web.Request("bgcolor", "cccccc");
                DataRow dr = BLL.Config.GetInfoOfVip();
                if (dr != null)
                {
                  
                    MoneyToViptimeWeek = Convert.ToInt32(dr["MoneyToViptimeWeek"]);
                    MoneyToViptimeMonth = Convert.ToInt32(dr["MoneyToViptimeMonth"]);
                    MoneyToViptimeHYear = Convert.ToInt32(dr["MoneyToViptimeHYear"]);
                    MoneyToViptimeYear = Convert.ToInt32(dr["MoneyToViptimeYear"]);
                }
                string vipt = CommonManager.Web.Request("viptype", "7");

                switch (vipt)
                {
                    case "7": lblMsg.Text = MoneyToViptimeWeek.ToString(); break;
                    case "30": lblMsg.Text = MoneyToViptimeMonth.ToString(); break;
                    case "180": lblMsg.Text = MoneyToViptimeHYear.ToString(); break;
                    case "360": lblMsg.Text = MoneyToViptimeYear.ToString(); break;


                }
              
            }
        }
 
 

    }
}
