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
using Bzw.E;
using UiCommon;
using BCST.Common;

namespace Bzw.Inhersits.Manage
{
    public partial class Manage_ExchangeMoneyLog : UiCommon.ManageBasePage
    {

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
        /// rpList 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Repeater rpList;

        /// <summary>
        /// ltNonData 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Literal ltNonData;

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
        protected int PageIndex
        {
            get
            {
                string tmp = CommonManager.Web.Request("page", "");
                if (string.IsNullOrEmpty(tmp) || !CommonManager.String.IsInteger(tmp))
                    return 1;
                return int.Parse(tmp);
            }
        }

        protected void Page_Load(object sender, EventArgs e)
        {
            //设置公共条件
            WhereClip where = Web_VAgentMoneyLog._.UserID == UserLoginInfo.UserID;
            //读取
            DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
                .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
                .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
                .AddInputParameter("@Columns", DbType.String, "*")
                .AddInputParameter("@TableName", DbType.String, "Web_VAgentMoneyLog")
                .AddInputParameter("@Wheres", DbType.String, " and " + DbSession.Default.Serialization(where))
                .AddInputParameter("@KeyName", DbType.String, "ID")
                .AddInputParameter("@OrderBy", DbType.String, "InputDate desc")
                .ToDataSet();
            if (ds.Tables.Count > 0)
            {
                anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
                anpPageIndex.CurrentPageIndex = PageIndex;
                if (ds.Tables[1].Rows.Count > 0)
                {
                    rpList.DataSource = ds.Tables[1];
                    rpList.DataBind();
                    rpList.Visible = true;
                    ltNonData.Visible = false;
                }
                else
                {
                    rpList.Visible = false;
                    ltNonData.Visible = true;
                }
            }
            else
            {
                rpList.Visible = false;
                ltNonData.Visible = true;
            }
        }
    }
}
