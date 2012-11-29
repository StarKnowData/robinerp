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
using Bzw.Entities;
using Bzw.Data;
using UiCommon;
namespace Bzw.Inhersits.Manage
{
    public partial class Manage_PicList : UiCommon.ManageBasePage
    {

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
        /// rptAlbumColumnList 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Repeater rptAlbumColumnList;

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
                string pi = CommonManager.Web.Request("page", "");
                if (string.IsNullOrEmpty(pi) || !CommonManager.String.IsInteger(pi))
                    return 1;
                return int.Parse(pi);
            }
        }

        protected string ColumnName = "全部";

        private int ColumnID
        {
            get
            {
                string tmp = CommonManager.Web.Request("params", "0");
                if (string.IsNullOrEmpty(tmp) || tmp == "0" || !CommonManager.String.IsInteger(tmp))
                    return 0;
                return int.Parse(tmp);
            }
        }

        protected void Page_Load(object sender, EventArgs e)
        {
            if (!UserLoginInfo.IsLogin)
                Response.Redirect("/");

            TUsers model = DbSession.Default.Get<TUsers>(TUsers._.UserName == UserLoginInfo.UserName);

            if (model == null)
                Response.Redirect("/");

            WhereClip where = VUsersAlbum._.UserID == model.UserID;
            if (ColumnID != 0)
            {
                Web_UserAlbumColumn column = DbSession.Default.Get<Web_UserAlbumColumn>(Web_UserAlbumColumn._.ID == ColumnID);
                if (column != null)
                {
                    where &= VUsersAlbum._.ColumnID == ColumnID;
                    ColumnName = column.AlbumName;
                }
            }

            anpPageIndex.RecordCount = DbSession.Default.Count<VUsersAlbum>(where);
            anpPageIndex.CurrentPageIndex = PageIndex;
            anpPageIndex.PageSize = anpPageIndex.PageSize;

            DataTable dt = DbSession.Default.FromProc("Bzw_GetPager")
                .AddInputParameter("@QueryStr", DbType.String, "select * from VUsersAlbum where " + string.Format(where.ToString(), "", ""))
            .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
            .AddInputParameter("@PageCurrent", DbType.Int32, PageIndex)
            .AddInputParameter("@FdShow", DbType.String, "*")
            .AddInputParameter("@FdOrder", DbType.String, "InputTime desc")
            .ToDataTable();

            //DataTable dt = DbSession.Default.From<Web_UserAlbumColumn>().Where(Web_UserAlbumColumn._.UserID == model.UserID).OrderBy(Web_UserAlbumColumn._.InputTime.Desc).ToDataTable();
            if (dt.Rows.Count > 0)
            {
                rptAlbumColumnList.DataSource = dt;
                rptAlbumColumnList.DataBind();
            }
        }
    }
}
