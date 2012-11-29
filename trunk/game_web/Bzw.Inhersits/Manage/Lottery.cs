using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using Bzw.Data;

namespace Bzw.Inhersits.Manage
{
     public partial class Manage_Lottery : UiCommon.ManageBasePage
    {
        /// <summary>
        /// Head1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlHead Head1;

        /// <summary>
        /// webmeta1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webmeta1;

        /// <summary>
        /// webtop1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webtop1;

        /// <summary>
        /// webuserlogin1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webuserlogin1;

        /// <summary>
        /// webservice1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webservice1;



        /// <summary>
        /// webfooter1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webfooter1;
        public string ZJContent;
        public Int64 gMoney=0;
        public Int64 sMoney=0;
        public Int64 jMoney=0;
        public Int64 userMoney = 0;
        protected void Page_Load(object sender, EventArgs e)
        {
            DataTable dt = DbSession.Default.FromSql("select * from Web_LotterConfig").ToDataTable();
            if (dt.Rows.Count > 0)
            {
                gMoney =Convert.ToInt64( dt.Rows[0]["GoldMoney"]);
                sMoney = Convert.ToInt64(dt.Rows[0]["SilverMoney"]);
                jMoney = Convert.ToInt64(dt.Rows[0]["JadeMoney"]);
            }
            userMoney =Convert.ToInt64( new BLL.Member().GetBankMoney(UiCommon.UserLoginInfo.UserID));
            object obj = DbSession.Default.FromSql("select top 1 [Content] from  Web_NewsData where News_Type in (select typeid from Web_NewsType where TypeName='中奖名单')").ToScalar();
            ZJContent = (obj == null) ? "" : obj.ToString();
        }

    }
}
