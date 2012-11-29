using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;


namespace Bzw.Inhersits
{
    public partial class Manage_Pay_JFTpay_NotityReceive : UiCommon.BasePage 
    {

        /// <summary>
        /// Form1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlForm Form1;

        /// <summary>
        /// id 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlGenericControl id;

        /// <summary>
        /// state 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlGenericControl state;


        protected void Page_Load(object sender, EventArgs e)
        {
            string opstate = Request.QueryString["opstate"];
            string st = "";
            if (opstate == "0")
            {
                st = "成功";
            }
            else
            {
                st = "失败";
            }
            this.id.InnerText = Request.QueryString["orderid"];
            this.state.InnerText = st;
        }

    }
}
