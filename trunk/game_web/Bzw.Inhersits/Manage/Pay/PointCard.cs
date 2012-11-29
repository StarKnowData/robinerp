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
using Bzw.WebLibrary;

namespace Bzw.Inhersits.Manage.Pay
{
    public partial class Manage_Pay_PointCard :UiCommon.BasePage
    {
          /// <summary>
    /// Manage_Pay_PointCard 类。
    /// </summary>
    /// <remarks>
    /// 自动生成的类。
    /// </remarks>

        
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
        /// 
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
        /// Form1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlForm Form1;
        
        /// <summary>
        /// lblMsg 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Label lblMsg;
        
        /// <summary>
        /// txtUserName 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtUserName;
        
        /// <summary>
        /// txtUserName2 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtUserName2;
        
        /// <summary>
        /// txtCardNo 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtCardNo;
        
        /// <summary>
        /// txtCardPwd 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtCardPwd;
        
        /// <summary>
        /// txtValidCode 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtValidCode;
        
        /// <summary>
        /// imageField2 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputSubmit imageField2;
        
        /// <summary>
        /// webfooter1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webfooter1;
        /// <summary>
        /// ddlGameList 控件
        /// </summary>
        protected global::System.Web.UI.WebControls.DropDownList ddlGameList;

        protected global::System.Web.UI.WebControls.RadioButtonList rblPayType;

        protected void Page_Load(object sender, EventArgs e)
        {
            SeoSetting(SeoConfig.Config.DefaultSeo);
            if (!IsPostBack)
            {
                if (UiCommon.UserLoginInfo.IsLogin)
                {
                    txtUserName.Text = UiCommon.UserLoginInfo.UserName;
                    txtUserName2.Text = UiCommon.UserLoginInfo.UserName;
                }

                DataTable dt = DbSession.Default.FromSql("SELECT NameID,ComName FROM dbo.TGameNameInfo WHERE NameID IN (SELECT GameNameID FROM dbo.TGameRoomInfo WHERE GameTypeID=1 GROUP BY GameNameID) ORDER BY dbo.TGameNameInfo.IDSort").ToDataTable();

                
             
                ddlGameList.DataSource = dt;
                ddlGameList.DataTextField = "ComName";
                ddlGameList.DataValueField = "NameID";
                ddlGameList.DataBind();
                
            }

        }
        
        protected void button5_ServerClick(object sender, EventArgs e)
        {
            if (!BCST.Common.CommonManager.Web.CheckPostSource())
                return;
            //1.校验验证码
            if (UiCommon.ValidCode.CurrentCode == null)
            {
                lblMsg.Text = "验证码已过期，请输入新的验证码！";
                txtValidCode.Text = string.Empty;
                return;
            }
            else if (txtValidCode.Text.Trim() != UiCommon.ValidCode.CurrentCode)
            {
                lblMsg.Text = "验证码输入错误，请输入新的验证码！";
                txtValidCode.Text = string.Empty;
                return;
            }

            //2.判断用户名是否存在
            BLL.Member member = new BLL.Member();
            string userName = Utility.Common.SqlEncode(txtUserName.Text.Trim());
            if (!member.ExistName(userName))
            {
                lblMsg.Text = "您输入的游戏帐号(用户名)不存在！";
                txtValidCode.Text = string.Empty;
                return;
            }
            //判断玩家充值时，不能在游戏中
            if (member.IsInRoomOrGame(userName))
            {
                lblMsg.Text = "要充值的帐号正在游戏中，请先退出游戏再进行充值！";
                txtValidCode.Text = string.Empty;
                return;
               
            }
            //3.判断充值卡是否已充值，或卡号及密码错误
            string cardNo = Utility.Common.SqlEncode(txtCardNo.Text.Trim());
            string cardPwd = Utility.Common.SqlEncode(txtCardPwd.Text.Trim());
            int cardState = new BLL.Card().PointCardState(cardNo, cardPwd);
            if (cardState == -1)
            {
                lblMsg.Text = "对不起，您输入的卡号或密码有误！";
                txtValidCode.Text = string.Empty;
                return;
            }
            else if (cardState == 1)
            {
                lblMsg.Text = "对不起，您输入的卡号已经被充值！";
                txtValidCode.Text = string.Empty;
                return;
            }

            #region 免费卡
            
		// 免费卡的张数
        int freeCardForUser = 0;
        DataRow dr = member.GetFreeCardCount();
        if (dr != null)
        {
            freeCardForUser = Convert.ToInt32(dr["FreeCardCount"]);
        }
        
        
        //若是免费卡，先判断用户是否已经充值了XX张。如：免费卡每个用户只能充值2张。
        if (member.IsFreeCard(cardNo))
        {
            int cardCount = member.FreeCardCount(userName);
            if (cardCount >= freeCardForUser)
            {
                lblMsg.Text = "您已经使用" + freeCardForUser + "张免费卡了！";
                txtValidCode.Text = string.Empty;
                return;
            }
		} 
            #endregion

            //4.将充值金额转换成金币存入银行
            //被充值用户如果有推荐人，在Web_Config中根据参数值奖励推荐人
            //更新点卡状态
            //by YMH 2012-9-4  充值积分
         //积分充值存在
        if (ConfigurationManager.AppSettings["IsPayToPoint"] == "1" && rblPayType.SelectedValue=="point" && ddlGameList.SelectedValue!="")
        { 
            //充值积分
            int result = member.PointCardFull2(userName, cardNo, cardPwd, Utility.Common.RequestIP,ddlGameList.SelectedValue);
            if (result == 0)
            {
                lblMsg.Text = "充值卡[" + cardNo + "]充值成功，充值的游戏帐号(用户名)是" + userName + "！" + DateTime.Now;
                txtUserName.Text = string.Empty;
                txtUserName2.Text = string.Empty;
                txtCardNo.Text = string.Empty;
                txtValidCode.Text = string.Empty;
            }
            else if (result == -1)
            {
                lblMsg.Text = "抱歉，点卡不存在或点卡号、密码不正确！";
                txtValidCode.Text = string.Empty;
            }
            else
            {
                lblMsg.Text = "抱歉，点卡充值失败，可能是服务器繁忙，请稍候再试！";
                txtValidCode.Text = string.Empty;
            }
        }
        else//充值金币
        {
            if (member.PointCardFull(userName, cardNo, cardPwd, Utility.Common.RequestIP))
            {
                lblMsg.Text = "充值卡[" + cardNo + "]充值成功，充值的游戏帐号(用户名)是" + userName + "！" + DateTime.Now;
                txtUserName.Text = string.Empty;
                txtUserName2.Text = string.Empty;
                txtCardNo.Text = string.Empty;
                txtValidCode.Text = string.Empty;
            }
            else
            {
                lblMsg.Text = "抱歉，点卡充值失败，可能是服务器繁忙，请稍候再试！";
                txtValidCode.Text = string.Empty;
            }
        }
        }
    }
}
