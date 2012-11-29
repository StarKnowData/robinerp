using System;
using System.Collections.Generic;
using System.Text;
using Utility;
using BCST.Common;
using System.Data;
using Bzw.Data;
using System.Configuration;

namespace Bzw.Inhersits.Manage
{
    public partial class Manage_ClothDetail : UiCommon.ManageBasePage
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
        /// webservice1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webservice1;

        /// <summary>
        /// webfooter1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webfooter1;
        protected global::System.Web.UI.WebControls.HiddenField hidId;
        public string Cid;
        public string LogName, Price, SendLotteries, Descript,ImgSrc,LogID;
        protected void Page_Load(object sender, EventArgs e)
        {
           
                BindData();
             
        }
        public void BindData()
        {
            Cid = Common.SqlEncode(Common.GetStringOfUrl("id"));
            if (string.IsNullOrEmpty(Cid) || !CommonManager.String.IsInteger(Cid))
            {
                Response.Write("<script>alert('请不要尝试非法操作。');history.back();</script>");
                Response.End();
                return;
            }
            hidId.Value = Cid;
            DataTable dt = DbSession.Default.FromSql("select * from Web_Clothes where id =" + Cid).ToDataTable();
            if (dt.Rows.Count > 0)
            {
                LogName = dt.Rows[0]["LogName"].ToString();
                Price = dt.Rows[0]["Price"].ToString();
                SendLotteries = dt.Rows[0]["SendLotteries"].ToString();
                Descript = dt.Rows[0]["Descript"].ToString();
                LogID = dt.Rows[0]["LogID"].ToString();
                ImgSrc =  "/Image/Users/"+((dt.Rows[0]["Sex"].ToString() == "True")  ? "b_" +(Convert.ToInt32( dt.Rows[0]["LogID"].ToString() )+1)+ ".png" : "g_" +  (Convert.ToInt32(dt.Rows[0]["LogID"].ToString())+1)+ ".png");
            }
            else
            {
                Response.Write("<script>alert('您所查看的服装不存在或已被删除！');history.back();</script>");
                Response.End();
                return;
            }
        }
        protected void btnBuy_Click(object sender, EventArgs e)
        {
            if (!CommonManager.Web.CheckPostSource())
                return;

            BLL.Member member = new BLL.Member();
            //if (member.IsInRoomOrGame(UiCommon.UserLoginInfo.UserName))
            //{
                 
            //    BCST.Common.CommonManager.Web.RegJs(this, "alert('抱歉，您的帐号已进入房间中或正在游戏中，不能进行服装购买操作！');history.back();", true);
            //    return;
            //}
             
            Dictionary<string, object> dic = new Dictionary<string, object>();
            DbSession.Default.FromProc("Web_pClothBuy").AddInputParameter("@UserID", DbType.Int32, UiCommon.UserLoginInfo.UserID)
                .AddInputParameter("@ClothID", DbType.Int32, hidId.Value)
                .AddReturnValueParameter("@ReturnValue", DbType.Int32)
               .Execute(out dic);
            if (dic.Count <= 0)
                CommonManager.Web.RegJs(this, "alert('抱歉，购买失败，可能是服务器繁忙，请稍后再试！');location.href=location.href;", true);

            if (dic["ReturnValue"].ToString() == "-1")
            {
                CommonManager.Web.RegJs(this, "alert('抱歉，购买失败，您的" + ConfigurationManager.AppSettings["moneyName"].ToString() + "不足！');location.href=location.href;", true);
            }
            if (dic["ReturnValue"].ToString() == "-2")
            {
                CommonManager.Web.RegJs(this, "alert('抱歉，购买失败，可能是服务器繁忙，请稍后再试！');location.href=location.href;", true);
            }
            if (dic["ReturnValue"].ToString() == "-3")
            {
                CommonManager.Web.RegJs(this, "alert('抱歉，请购买与您性别一致的服装！');location.href=location.href;", true);
            }
            string token = Utility.Common.GetStringOfUrl("token");

            if (token.Trim().Length > 0 && token == "plateform")
            {

                CommonManager.Web.RegJs(this, "alert('购买成功！');location.href='bzw://avatar/change?UserID=" + UiCommon.UserLoginInfo.UserID + "&NewLogoID=" + LogID + "&Price=" + Price + "';", true);
            }
            else
            {
                CommonManager.Web.RegJs(this, "alert('购买成功！');location.href=location.href;", true);
            }
        }
    }
}
