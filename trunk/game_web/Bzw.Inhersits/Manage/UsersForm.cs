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
using Bzw.Entities;
using System.IO;
using UiCommon;
using System.Collections.Generic;


namespace Bzw.Inhersits.Manage
{
    public partial class Manage_UsersForm : UiCommon.BasePage
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!CommonManager.Web.CheckPostSource())
                CommonManager.Web.ResponseEnd("/", true);
            string param = CommonManager.Web.Request("params", "");
            if (string.IsNullOrEmpty(param))
                return;

            switch (param)
            {
                case "addpic":
                    AddPic();
                    break;
                case "delalbumcover":
                    DelAlbumCover();
                    break;
                case "setalbumpublic":
                    SetAlbumPublic();
                    break;
                case "delpic":
                    DelPic();
                    break;
                case "delalbumcolumn":
                    DelAlbumColumn();
                    break;
                case "addalbumcolumn":
                    AddAlbumColumn();
                    break;
                case "setalbumtop":
                    SetAlbumTop();
                    break;
                case "settocover":
                    SetToCover();
                    break;
                default:
                    CommonManager.Web.ResponseEnd("/", true);
                    break;
            }
        }

        #region 设置某张照片为相册封面
        /// <summary>
        /// 设置某张照片为相册封面
        /// </summary>
        private void SetToCover()
        {
            if (!UserLoginInfo.IsLogin)
            {
                Response.Write("请先登录。");
                return;
            }
            TUsers user = DbSession.Default.Get<TUsers>(TUsers._.UserID == UserLoginInfo.UserID);
            if (user == null)
            {
                Response.Write("请先登录。");
                return;
            }

            string aid = CommonManager.Web.Request("id", "");

            if (string.IsNullOrEmpty(aid) || !CommonManager.String.IsInteger(aid))
            {
                Response.Write("请不要尝试非法操作。");
                return;
            }
            Web_UserAlbum pic = DbSession.Default.Get<Web_UserAlbum>(Web_UserAlbum._.ID == aid && Web_UserAlbum._.UserID == user.UserID);
            if (pic == null)
            {
                Response.Write("请不要尝试非法操作。");
                return;
            }

            Web_UserAlbumColumn column = DbSession.Default.Get<Web_UserAlbumColumn>(Web_UserAlbumColumn._.ID == pic.ColumnID);
            column.Cover = pic.PicPath;
            column.Attach();
            DbSession.Default.Save<Web_UserAlbumColumn>(column);
            Response.Write("success");
        }
        #endregion

        #region 设置某个相册排序数字最大
        /// <summary>
        /// 设置某个相册排序数字最大
        /// </summary>
        private void SetAlbumTop()
        {
            if (!UserLoginInfo.IsLogin)
            {
                Response.Write("请先登录。");
                return;
            }
            TUsers user = DbSession.Default.Get<TUsers>(TUsers._.UserID == UserLoginInfo.UserID);
            if (user == null)
            {
                Response.Write("请先登录。");
                return;
            }

            string aid = CommonManager.Web.Request("id", "");

            if (string.IsNullOrEmpty(aid) || !CommonManager.String.IsInteger(aid))
            {
                Response.Write("请不要尝试非法操作。");
                return;
            }
            Web_UserAlbumColumn column = DbSession.Default.Get<Web_UserAlbumColumn>(Web_UserAlbumColumn._.ID == aid && Web_UserAlbumColumn._.UserID == user.UserID);
            if (column == null)
            {
                Response.Write("请不要尝试非法操作。");
                return;
            }

            int max = (int)DbSession.Default.Max<Web_UserAlbumColumn>(Web_UserAlbumColumn._.OrderID, Web_UserAlbumColumn._.UserID == UserLoginInfo.UserID);
            column.OrderID = max + 1;
            column.Attach();
            DbSession.Default.Save<Web_UserAlbumColumn>(column);
            Response.Write("success");
        }
        #endregion

        #region 添加或修改一张照片
        /// <summary>
        /// 添加或修改一张照片
        /// </summary>
        private void AddPic()
        {
            if (!UserLoginInfo.IsLogin)
            {
                Response.Write("您尚未登录。<a href='javascript:history.back();'>点此返回上一页</a>");
                return;
            }

            TUsers model = DbSession.Default.Get<TUsers>(TUsers._.UserName == UserLoginInfo.UserName);

            if (model == null)
            {
                Response.Write("您尚未登录。<a href='javascript:history.back();'>点此返回上一页</a>");
                return;
            }
            //获取表单值
            string lcover = "";

            //判断是否有相册
            string columnid = CommonManager.Web.RequestForm("selColumnId", "");
            if (string.IsNullOrEmpty(columnid) || !CommonManager.String.IsInteger(columnid))
            {
                Response.Write("没有相册，请先创建相册。<a href='/Manage/AlbumWrite.aspx'>点击创建相册</a>");
                return;
            }

            if (Request.Files.Count > 0)
            {
                try
                {
                    if (!CommonManager.File.UploadFile(Request.Files["filePicPath"], 100 * 1024, new string[] { "jpg", "jpeg", "gif", "bmp", "png" }, "/Upload/Photo/" + model.UserID.ToString(), FileOperator.RenameType.流水号, out lcover))
                    {
                        lcover = "";
                    }
                }
                catch (Exception ex)
                {
                    Response.Write("文件上传错误：" + ex.Message + "<a href='javascript:history.back();'>点此返回上一页</a>");
                    return;
                }
            }
            string pname = Server.HtmlEncode(CommonManager.Web.RequestForm("txtPicName", ""));
            string pdes = Server.HtmlEncode(CommonManager.Web.RequestForm("txtPicDescription", ""));
            string shortnum = CommonManager.Web.RequestForm("txtShortNum", "1");
            string id = CommonManager.Web.Request("id", "");

            //校验
            if (string.IsNullOrEmpty(id) || !CommonManager.String.IsInteger(id))
            {
                if (string.IsNullOrEmpty(lcover))
                {
                    Response.Write("请上传您的照片。<a href='javascript:history.back();'>点此返回上一页</a>");
                    return;
                }
            }
            if (string.IsNullOrEmpty(pname) && !string.IsNullOrEmpty(lcover))
            {
                pname = lcover.Substring(lcover.LastIndexOf('/') + 1);
            }
            //存入数据库
            Web_UserAlbum pic;
            if (string.IsNullOrEmpty(id) || !CommonManager.String.IsInteger(id))
            {
                pic = new Web_UserAlbum();
                pic.InputTime = DateTime.Now;
                pic.UserID = model.UserID;
                pic.Enable = Library.EnableState.未处理.ToString();
            }
            else
            {
                pic = DbSession.Default.Get<Web_UserAlbum>(Web_UserAlbum._.ID == id);
                pic.Attach();
            }
            pic.ColumnID = int.Parse(columnid);
            pic.PicDescription = pdes;
            pic.PicName = pname;
            pic.PicPath = string.IsNullOrEmpty(pic.PicPath) ? lcover : pic.PicPath;
            pic.ShortNum = (string.IsNullOrEmpty(shortnum) || !CommonManager.String.IsInteger(shortnum)) ? 1 : int.Parse(shortnum);

            DbSession.Default.Save<Web_UserAlbum>(pic);
            //反馈
            Response.Write("<script>location.href='PicList.aspx';</script>");
        }
        #endregion

        #region 删除一个相册封面
        /// <summary>
        /// 删除一个相册封面
        /// </summary>
        private void DelAlbumCover()
        {

            if (!UserLoginInfo.IsLogin)
            {
                Response.Write("您尚未登录。");
                return;
            }

            TUsers model = DbSession.Default.Get<TUsers>(TUsers._.UserName == UserLoginInfo.UserName);

            if (model == null)
            {
                Response.Write("您尚未登录。");
                return;
            }

            string tmp = CommonManager.Web.Request("id", "");
            if (string.IsNullOrEmpty(tmp) || !CommonManager.String.IsInteger(tmp) || !DbSession.Default.Exists<Web_UserAlbumColumn>(Web_UserAlbumColumn._.ID == tmp))
            {
                Response.Write("非法操作。");
                return;
            }

            Web_UserAlbumColumn album = DbSession.Default.Get<Web_UserAlbumColumn>(Web_UserAlbumColumn._.ID == tmp);
            if (album == null)
            {
                Response.Write("非法操作。");
                return;
            }

            CommonManager.File.DeleteFile(album.Cover);

            DbSession.Default.Update<Web_UserAlbumColumn>(Web_UserAlbumColumn._.Cover, "", Web_UserAlbumColumn._.ID == tmp);

            Response.Write("success");
        }
        #endregion

        #region 添加或修改一个相册
        /// <summary>
        /// 添加或修改一个相册
        /// </summary>
        private void AddAlbumColumn()
        {

            if (!UserLoginInfo.IsLogin)
            {
                Response.Write("您尚未登录。<a href='javascript:history.back();'>点此返回上一页</a>");
                return;
            }

            TUsers model = DbSession.Default.Get<TUsers>(TUsers._.UserName == UserLoginInfo.UserName);

            if (model == null)
            {
                Response.Write("您尚未登录。<a href='javascript:history.back();'>点此返回上一页</a>");
                return;
            }

            //获取表单数据
            string name = CommonManager.Web.RequestForm("txtAlbumName", "");
            string ucover = CommonManager.Web.RequestForm("txtCover", "");

            string lcover = "";
            if (Request.Files.Count > 0)
            {
                try
                {
                    if (!CommonManager.File.UploadFile(Request.Files["fileCover"], 100 * 1024, new string[] { "jpg", "jpeg", "gif", "bmp", "png" }, "/Upload/UserAlbum", FileOperator.RenameType.流水号, out lcover))
                    {
                        lcover = "";
                    }
                }
                catch (Exception ex)
                {
                    Response.Write("文件上传错误：" + ex.Message + "<a href='javascript:history.back();'>点此返回上一页</a>");
                    return;
                }
            }

            string ispublic = CommonManager.Web.RequestForm("rdoIsPublic", Library.PublicState.公开.ToString());
            //校验
            if (string.IsNullOrEmpty(name))
            {
                Response.Write("请填写相册名称。<a href='javascript:history.back();'>点此返回上一页</a>");
                return;
            }
            //填充数据库
            string cur = CommonManager.Web.Request("cur", "");
            Web_UserAlbumColumn album;
            if (string.IsNullOrEmpty(cur))
            {
                album = new Web_UserAlbumColumn();
                album.InputTime = DateTime.Now;
                album.UserID = model.UserID;
            }
            else
            {
                album = DbSession.Default.Get<Web_UserAlbumColumn>(Web_UserAlbumColumn._.ID == cur);
                album.Attach();
            }
            album.AlbumName = name;
            album.Cover = string.IsNullOrEmpty(album.Cover) ? (string.IsNullOrEmpty(lcover) ? ucover : lcover) : album.Cover;
            album.IsPublic = ispublic;
            DbSession.Default.Save<Web_UserAlbumColumn>(album);
            //返回信息
            Response.Write("<script>location.href='Album.aspx';</script>");
        }
        #endregion

        #region 删除一个相册
        /// <summary>
        /// 删除一个相册
        /// </summary>
        private void DelAlbumColumn()
        {
            string aid = CommonManager.Web.Request("id", "");
            #region 校验

            if (!UserLoginInfo.IsLogin)
            {
                Response.Write("您尚未登录。");
                return;
            }

            TUsers model = DbSession.Default.Get<TUsers>(TUsers._.UserName == UserLoginInfo.UserName);

            if (model == null)
            {
                Response.Write("您尚未登录。");
                return;
            }

            if (string.IsNullOrEmpty(aid) || !CommonManager.String.IsInteger(aid))
            {
                Response.Write("请不要尝试非法操作。");
                return;
            }

            if (!DbSession.Default.Exists<Web_UserAlbumColumn>(Web_UserAlbumColumn._.ID == aid))
            {
                Response.Write("请不要尝试非法操作。");
                return;
            }
            #endregion

            //转移
            //Web_UserAlbumColumn album = DbSession.Default.Get<Web_UserAlbumColumn>( Web_UserAlbumColumn._.ID == ( DbSession.Default.Max<Web_UserAlbumColumn>( Web_UserAlbumColumn._.ID, Web_UserAlbumColumn._.UserID == model.UserID ) ) );
            DataTable dt = DbSession.Default.From<Web_UserAlbumColumn>().Where(Web_UserAlbumColumn._.UserID == UserLoginInfo.UserID).ToDataTable();
            if (dt.Rows.Count > 1)
            {
                //仍有其他相册，则将当前相册下的照片转移
                //DataRow[] rows = dt.Select( "ID=" + aid );
                //if( rows.Length <= 0 )
                //    return;
                //dt.Rows.Remove(rows[0]);
                string maxid = dt.Compute("max(ID)", "ID<>" + aid).ToString();
                DbSession.Default.Update<Web_UserAlbum>(Web_UserAlbum._.ColumnID, maxid, Web_UserAlbum._.ColumnID == aid && Web_UserAlbum._.UserID == UserLoginInfo.UserID);
            }
            else
            {
                //不存在相册了，则不删除，仅将相册改名
                DbSession.Default.Update<Web_UserAlbumColumn>(Web_UserAlbumColumn._.AlbumName, "默认相册", Web_UserAlbumColumn._.ID == aid);
                Response.Write("success");
                return;
            }

            DbSession.Default.Delete<Web_UserAlbumColumn>(Web_UserAlbumColumn._.ID == aid);

            Response.Write("success");
        }
        #endregion

        #region 删除一张照片
        /// <summary>
        /// 删除一张照片
        /// </summary>
        private void DelPic()
        {
            string aid = CommonManager.Web.Request("id", "");
            string type = CommonManager.Web.Request("type", "0");

            #region 校验
            if (string.IsNullOrEmpty(aid) || !CommonManager.String.IsInteger(aid))
            {
                Response.Write("请不要尝试非法操作。");
                return;
            }

            if (!DbSession.Default.Exists<Web_UserAlbum>(Web_UserAlbum._.ID == aid))
            {
                Response.Write("请不要尝试非法操作。");
                return;
            }

            if (!UserLoginInfo.IsLogin)
            {
                Response.Write("您尚未登录。");
                return;
            }

            TUsers model = DbSession.Default.Get<TUsers>(TUsers._.UserName == UserLoginInfo.UserName);

            if (model == null)
            {
                Response.Write("您尚未登录。");
                return;
            }
            #endregion

            Web_UserAlbum album = DbSession.Default.Get<Web_UserAlbum>(Web_UserAlbum._.ID == aid);
            CommonManager.File.DeleteFile(album.PicPath);
            if (type == "1")
                DbSession.Default.Delete<Web_UserAlbum>(album);
            else if (type == "0")
                DbSession.Default.Update<Web_UserAlbum>(Web_UserAlbum._.PicPath, "", Web_UserAlbum._.ID == aid);

            Response.Write("success");
        }
        #endregion

        #region 设置用户相册的公开状态
        /// <summary>
        /// 设置用户相册的公开状态
        /// </summary>
        private void SetAlbumPublic()
        {
            string state = CommonManager.Web.Request("public", "");
            string aid = CommonManager.Web.Request("id", "");

            #region 校验
            if (string.IsNullOrEmpty(state) || string.IsNullOrEmpty(aid) || !CommonManager.String.IsInteger(state) || !CommonManager.String.IsInteger(aid))
            {
                Response.Write("请不要尝试非法操作。");
                return;
            }

            if (!DbSession.Default.Exists<Web_UserAlbumColumn>(Web_UserAlbumColumn._.ID == aid))
            {
                Response.Write("请不要尝试非法操作。");
                return;
            }

            //string UserName = uc.GetUserName.ToString();
            if (!UserLoginInfo.IsLogin)
            {
                Response.Write("您尚未登录。");
                return;
            }

            TUsers model = DbSession.Default.Get<TUsers>(TUsers._.UserName == UserLoginInfo.UserName);

            if (model == null)
            {
                Response.Write("您尚未登录。");
                return;
            }

            if (!DbSession.Default.Exists<Web_UserAlbumColumn>(Web_UserAlbumColumn._.ID == aid && Web_UserAlbumColumn._.UserID == model.UserID))
            {
                Response.Write("操作非法。");
                return;
            }
            #endregion

            DbSession.Default.Update<Web_UserAlbumColumn>(Web_UserAlbumColumn._.IsPublic, ((Library.PublicState)int.Parse(state)).ToString(), Web_UserAlbumColumn._.UserID == model.UserID && Web_UserAlbumColumn._.ID == aid);
            Response.Write("success");
        }
        #endregion
    }
}
