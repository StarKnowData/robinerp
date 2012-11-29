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
using Bzw.Entities;
using UiCommon;
using BCST.Common;


namespace Bzw.Inhersits.Manage
{
       

    public partial class Manage_Album : UiCommon.ManageBasePage
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
                string pi = CommonManager.Web.Request("page", ""); //Limit.getFormValue( "page" );
                if (string.IsNullOrEmpty(pi) || !CommonManager.String.IsInteger(pi))
                    return 1;
                return int.Parse(pi);
            }
        }

        protected void Page_Load(object sender, EventArgs e)
        {
            TUsers model = DbSession.Default.Get<TUsers>(TUsers._.UserName == UserLoginInfo.UserName);

            if (model == null)
                Response.Redirect("/");

            string where = " where UserID=" + model.UserID;

            anpPageIndex.RecordCount = DbSession.Default.Count<Web_vUserAlbumColumn>(new WhereClip(where.Replace("where", "")));
            anpPageIndex.CurrentPageIndex = PageIndex;
            anpPageIndex.PageSize = 6;

            DataTable dt = DbSession.Default.FromProc("Bzw_GetPager")
                .AddInputParameter("@QueryStr", DbType.String, "select * from Web_vUserAlbumColumn " + where)
            .AddInputParameter("@PageSize", DbType.Int32, anpPageIndex.PageSize)
            .AddInputParameter("@PageCurrent", DbType.Int32, PageIndex)
            .AddInputParameter("@FdShow", DbType.String, "*")
            .AddInputParameter("@FdOrder", DbType.String, "OrderID desc,InputTime desc")
            .ToDataTable();

            //DataTable dt = DbSession.Default.From<Web_UserAlbumColumn>().Where(Web_UserAlbumColumn._.UserID == model.UserID).OrderBy(Web_UserAlbumColumn._.InputTime.Desc).ToDataTable();
            if (dt.Rows.Count > 0)
            {
                rptAlbumColumnList.DataSource = dt;
                rptAlbumColumnList.DataBind();
            }
        }

        protected string GetPicCount(int albumID)
        {
            if (albumID == 0)
                return "";
            return DbSession.Default.Count<Web_UserAlbum>(Web_UserAlbum._.ColumnID == albumID).ToString();
        }
    }
}
