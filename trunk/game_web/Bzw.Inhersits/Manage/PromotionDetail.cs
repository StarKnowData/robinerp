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
using BCST.Common;
using Bzw.Data;
using System.Collections.Generic;
namespace Bzw.Inhersits.Manage
{
    public partial class Manage_PromotionDetail : UiCommon.ManageBasePage
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
        /// webuserlogin1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webuserlogin1;

        /// <summary>
        /// rpLog 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Repeater rpLog;

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
            string where = " and TGUserID=" + UiCommon.UserLoginInfo.UserID;
            DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
                    .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
                    .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
                    .AddInputParameter("@Columns", DbType.String, "*")
                    .AddInputParameter("@TableName", DbType.String, "web_vTGpayClearing")
                    .AddInputParameter("@Wheres", DbType.String, where)
                    .AddInputParameter("@KeyName", DbType.String, "RecordID")
                    .AddInputParameter("@OrderBy", DbType.String, "RecordID desc")
                    .ToDataSet();

            if (ds.Tables.Count > 0)
            {
                anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
                anpPageIndex.CurrentPageIndex = PageIndex;
                if (ds.Tables[1].Rows.Count > 0)
                {
                    ltNonData.Visible = false;
                    rpLog.Visible = true;
                    rpLog.DataSource = ds.Tables[1];
                    rpLog.DataBind();
                }
                else
                {
                    ltNonData.Visible = true;
                    rpLog.Visible = false;
                }
            }

            /*
            Dictionary<string, object> output = new Dictionary<string, object>();

            DataTable dt = DbSession.Default.FromProc( "Bzw_GetTuiGuangInfo" )
                .AddInputParameter( "@TG_UserID", DbType.Int32, UiCommon.UserLoginInfo.UserID )
                .AddInputParameter( "@PageSize", DbType.Int32, anpPageIndex.PageSize )
                .AddInputParameter( "@PageIndex", DbType.Int32, PageIndex )
                .AddOutputParameter( "@RecordCount", DbType.Int32, 4 )
                .ToDataTable( out output );

            anpPageIndex.RecordCount = (int)output["RecordCount"];
            anpPageIndex.CurrentPageIndex = PageIndex;

            if( dt.Rows.Count > 0 )
            {
                rpLog.DataSource = dt;
                rpLog.DataBind();
                rpLog.Visible = true;
                ltNonData.Visible = false;
            }
            else
            {
                ltNonData.Visible = true;
                rpLog.Visible = false;
            }
             */
        }
    }
}
