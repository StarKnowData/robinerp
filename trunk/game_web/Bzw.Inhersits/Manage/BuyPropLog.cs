using System;
using System.Data;
using System.Configuration;
using System.Collections;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using Bzw.Data;
using BCST.Common;
using System.Text;

namespace Bzw.Inhersits.Manage
{

    public partial class Manage_BuyPropLog : UiCommon.ManageBasePage
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
        /// Left1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl Left1;

        /// <summary>
        /// webuserlogin1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webuserlogin1;



        /// <summary>
        /// rpList 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Repeater rpList;

        /// <summary>
        /// anpPageIndex 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::Wuqi.Webdiyer.AspNetPager anpPageIndex;

        /// <summary>
        /// webfooter1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webfooter1;
        protected int Rowid = 0;
        protected int PageIndex
        {
            get
            {
                string pi = CommonManager.Web.Request("page", "");
                if (string.IsNullOrEmpty(pi) || !CommonManager.String.IsInteger(pi))
                    return 1;
                return int.Parse(pi);
            }
        }
        protected void Page_Load(object sender, EventArgs e)
        {
            StringBuilder where = new StringBuilder(" and userid=" + UiCommon.UserLoginInfo.UserID);

            string bd = CommonManager.Web.RequestUrlDecode("bd", "");
            string ed = CommonManager.Web.RequestUrlDecode("ed", "");
            if (!string.IsNullOrEmpty(bd) && CommonManager.String.IsDateTime(bd))
            {
                where.AppendFormat(" and ActionTime>='{0} 00:00:00'", bd);
            }
            if (!string.IsNullOrEmpty(ed) && CommonManager.String.IsDateTime(ed))
            {
                where.AppendFormat(" and ActionTime<='{0} 23:59:59'", ed);
            }

            DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
                    .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
                    .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
                    .AddInputParameter("@Columns", DbType.String, "*")
                    .AddInputParameter("@TableName", DbType.String, "Web_VBuyPropLog")
                    .AddInputParameter("@Wheres", DbType.String, where.ToString())
                    .AddInputParameter("@KeyName", DbType.String, "Id")
                    .AddInputParameter("@OrderBy", DbType.String, "ActionTime DESC")
                    .ToDataSet();

            if (ds.Tables.Count > 0)
            {
                anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
                anpPageIndex.CurrentPageIndex = PageIndex;

                if (ds.Tables[1].Rows.Count > 0)
                {

                    rpList.DataSource = ds.Tables[1];
                    rpList.DataBind();
                }

            }
        }
    }

}
