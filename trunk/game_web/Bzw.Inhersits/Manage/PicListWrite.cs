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
using Bzw.Entities;
using Bzw.Data;
using BCST.Common;
using UiCommon;

namespace Bzw.Inhersits.Manage
{
    public partial class Manage_PicListWrite : UiCommon.ManageBasePage
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
        /// webfooter1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webfooter1;
        protected Web_UserAlbum pic;

        protected DataTable ColumnList;

        protected void Page_Load(object sender, EventArgs e)
        {
            TUsers model = DbSession.Default.Get<TUsers>(TUsers._.UserName == UserLoginInfo.UserName);

            if (model == null)
            {
                Response.Redirect("/");
            }

            string tmp = CommonManager.Web.Request("params", "");
            if (!string.IsNullOrEmpty(tmp) && CommonManager.String.IsInteger(tmp))
            {
                pic = DbSession.Default.Get<Web_UserAlbum>(Web_UserAlbum._.ID == tmp);
            }

            if (!IsPostBack)
            {
                ColumnList = DbSession.Default.From<Web_UserAlbumColumn>().Select(Web_UserAlbumColumn._.ID, Web_UserAlbumColumn._.AlbumName).Where(Web_UserAlbumColumn._.UserID == model.UserID).OrderBy(Web_UserAlbumColumn._.OrderID.Desc && Web_UserAlbumColumn._.InputTime.Desc).ToDataTable();
                if (ColumnList.Rows.Count <= 0)
                {
                    Response.Write("<script>alert('您还没有创建相册！');location.href='AlbumWrite.aspx';</script>");
                    return;


                }
            }
        }
    }
}
