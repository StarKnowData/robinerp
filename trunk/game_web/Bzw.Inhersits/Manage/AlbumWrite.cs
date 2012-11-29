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
    public partial class Manage_AlbumWrite : UiCommon.ManageBasePage
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
        /// form1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlForm form1;

        /// <summary>
        /// txtAlbumName 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtAlbumName;

        /// <summary>
        /// RequiredFieldValidator1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.RequiredFieldValidator RequiredFieldValidator1;

        /// <summary>
        /// rdoIsPublic 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.RadioButtonList rdoIsPublic;

        /// <summary>
        /// btnSubmit 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Button btnSubmit;

        /// <summary>
        /// webfooter1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webfooter1;
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!IsPostBack)
            {
                CommonManager.Web.BindListControl(Enum.GetNames(typeof(Library.PublicState)), rdoIsPublic);
            }

            string tmp = CommonManager.Web.Request("params", "");

            if (!string.IsNullOrEmpty(tmp) && CommonManager.String.IsInteger(tmp))
            {
                Web_UserAlbumColumn album = DbSession.Default.Get<Web_UserAlbumColumn>(Web_UserAlbumColumn._.ID == tmp && Web_UserAlbumColumn._.UserID == UserLoginInfo.UserID);
                if (album != null && !IsPostBack)
                {
                    txtAlbumName.Text = album.AlbumName;
                    CommonManager.Web.SetListControlSelectedFromValue(rdoIsPublic, album.IsPublic);
                    btnSubmit.Text = "修改相册";
                }
            }
        }

        protected void btnSubmit_Click(object sender, EventArgs e)
        {
            if (!IsValid)
                return;
            if (!CommonManager.Web.CheckPostSource())
                return;

            string tmp = CommonManager.Web.Request("params", "");
            Web_UserAlbumColumn album;
            if (!string.IsNullOrEmpty(tmp) && CommonManager.String.IsInteger(tmp))
            {
                //修改
                album = DbSession.Default.Get<Web_UserAlbumColumn>(Web_UserAlbumColumn._.ID == tmp && Web_UserAlbumColumn._.UserID == UserLoginInfo.UserID);
                if (album == null)
                    return;
                album.Attach();
                SetModel(album);
            }
            else
            {
                //新建
                album = new Web_UserAlbumColumn();
                album.InputTime = DateTime.Now;
                album.OrderID = 0;
                album.Cover = "";
                album.UserID = int.Parse(UserLoginInfo.UserID);
                SetModel(album);
            }
            DbSession.Default.Save<Web_UserAlbumColumn>(album);
            CommonManager.Web.ResponseEnd("Album.aspx", true);
        }

        private void SetModel(Web_UserAlbumColumn model)
        {
            model.AlbumName = txtAlbumName.Text.Trim();
            model.Cover = model.Cover;
            model.IsPublic = (rdoIsPublic.SelectedIndex == -1) ? Library.PublicState.公开.ToString() : rdoIsPublic.SelectedItem.Value;
            model.OrderID = model.OrderID;
            model.UserID = model.UserID;
        }
    }
}
