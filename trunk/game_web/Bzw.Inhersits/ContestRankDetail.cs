using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using BCST.Common;
using Bzw.Data;
using Bzw.WebLibrary;

namespace Bzw.Inhersits
{
    public partial class ContestRankDetail : UiCommon.BasePage
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
        /// rankleft1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        //protected global::Public_RankLeft rankleft1;

        /// <summary>
        /// webservice1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webservice1;

        /// <summary>
        /// rpList 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Repeater rpList;

        /// <summary>
        /// webfooter1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webfooter1;

        /// <summary>
        /// anpPageIndex 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::Wuqi.Webdiyer.AspNetPager anpPageIndex;
        private int PageIndex
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
            SeoSetting(SeoConfig.Config.DefaultSeo);
            BindList();
        }

        public void BindList()
        {
            if (Request.QueryString["params"] != null && CommonManager.String.IsInteger(Request.QueryString["params"]))
            {
                

                DataSet ds = DbSession.Default.FromProc("Web_pGetDataPager")
               .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
               .AddInputParameter("@CurrentPage", DbType.Int32, PageIndex)
               .AddInputParameter("@Columns", DbType.String, "*")
               .AddInputParameter("@TableName", DbType.String, "Web_ContestRank")
               .AddInputParameter("@Wheres", DbType.String, " and contestid=" + Request.QueryString["params"])
               .AddInputParameter("@KeyName", DbType.String, "UserID")
               .AddInputParameter("@OrderBy", DbType.String, "ranknum asc,ContestCount desc ")
               .ToDataSet();

                if (ds.Tables.Count > 0)
                {
                    anpPageIndex.RecordCount = (int)ds.Tables[0].Rows[0][0];
                    anpPageIndex.CurrentPageIndex = PageIndex;

                    if (ds.Tables[1].Rows.Count > 0)
                    {
                        rpList.Visible = true;

                        rpList.DataSource = ds.Tables[1];
                        rpList.DataBind();
                    }
                    else
                    {
                        rpList.Visible = false;
                        
                    }
                }
                ds.Clear();
            }
        }
    }
}
