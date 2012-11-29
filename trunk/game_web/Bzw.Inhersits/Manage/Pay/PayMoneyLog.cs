using System;
using System.Collections.Generic;
using System.Text;
using BCST.Common;
using System.Data;
using Bzw.Data;

namespace Bzw.Inhersits.Manage.Pay
{
    public partial class Manage_Pay_PayMoneyLog: UiCommon.ManageBasePage
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
        public int Rowid = 0;
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
            BindLogList();
        }

        public void BindLogList()
        {
            DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
                .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
                .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
                .AddInputParameter("@Columns", DbType.String, "*")
                .AddInputParameter("@TableName", DbType.String, "Web_RMBCost")
                .AddInputParameter("@Wheres", DbType.String, " and paysuccess=1 and users_ids=" + UiCommon.UserLoginInfo.UserID)
                .AddInputParameter("@KeyName", DbType.String, "PayID")
                .AddInputParameter("@OrderBy", DbType.String, "PayID desc")
              .ToDataSet();


            if (ds.Tables.Count > 0 && ds.Tables[1].Rows.Count > 0)
            {
                anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
                anpPageIndex.CurrentPageIndex = PageIndex;

                rpList.DataSource = ds.Tables[1];
                rpList.DataBind();
            }
            else
            {
                rpList.Visible = false;
                anpPageIndex.Visible = false;
            }
        }
    }
}
