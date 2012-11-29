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

using Utility;
using UiCommon;
using BCST.Common;
using Bzw.Data;
using BCST.Cache;
using System.Collections.Generic;
using System.Text;
using BLL;

namespace Bzw.Inhersits.Manage
{


    public partial class Manage_GameReg : UiCommon.BasePage
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
        /// form1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlForm form1;

        /// <summary>
        /// Label1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Label Label1;

        /// <summary>
        /// btnSubmit 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputSubmit btnSubmit;
        //设置注册页面是否需要显示QQ字段
        public string needqq = System.Configuration.ConfigurationSettings.AppSettings["qq"];
		public string needrealname = System.Configuration.ConfigurationSettings.AppSettings["RealName"];
		public string needIDCard = System.Configuration.ConfigurationSettings.AppSettings["IDCard"];
        public string needProcted = System.Configuration.ConfigurationSettings.AppSettings["IsCardProtected"];
        protected void Page_Load(object sender, EventArgs e)
        {
            //ip限制判断和时间间隔判断，不符合规则则页面返回。
            DataTable dt = DbSession.Default.FromSql("select top 1 * from Web_Config").ToDataTable();
            if (dt.Rows.Count <= 0)
                return;

            //ip禁止设置
            string ipset = dt.Rows[0]["IPDisabled"].ToString();
            //重复注册间隔时间
            int timespan = (int)dt.Rows[0]["ReRegTimeSpan"];

            string userip = CommonManager.Web.GetIP();

            if (!string.IsNullOrEmpty(ipset))
            {
                List<string> iplist = new List<string>(ipset.Split(','));

                if (iplist.Contains("*.*.*.*"))//全部限制
                {
                    //CommonManager.Web.RegJs( this, "alert('当前暂停注册，请稍后再来尝试。');history.back;", false );
                    //return;
                    Response.Write("当前暂停注册，请稍后再来尝试。");
                    Response.End();
                }


                if (
                    iplist.Contains(userip) ||
                    iplist.Contains(CommonManager.String.CutIP(userip, 1)) ||
                    iplist.Contains(CommonManager.String.CutIP(userip, 2)) ||
                    iplist.Contains(CommonManager.String.CutIP(userip, 3))
                )
                {
                    Response.Write("您的IP段在被限制的范围内，不能进行注册，请联系我们的客服进行咨询。");
                    Response.End();
                    //CommonManager.Web.RegJs( this, "alert('您的IP段在被限制的范围内，不能进行注册，请联系我们的客服进行咨询。');history.back;", false );
                    //return;
                }
            }

            object lastRegDate = BCSTCache.Default.Get<CookiesCache>("RegDateTime");
            if (lastRegDate != null && CommonManager.String.IsDateTime(lastRegDate.ToString()))
            {
                if ((DateTime.Now - DateTime.Parse(lastRegDate.ToString())).TotalMinutes < timespan)
                {
                    Response.Write("请不要重复注册。");
                    Response.End();
                    //CommonManager.Web.RegJs( this, "alert('请不要重复注册。');history.back;", false );
                    //return;
                }
            }
            
        }
        protected void btnSubmit_ServerClick(object sender, EventArgs e)
        {
            string validcode = Common.GetStringOfForm("validcode");
            if (ValidCode.CurrentCode != validcode)
            {
                Label1.Text = "温馨提示：验证码输入错误，请重新输入！";
                Label1.Visible = true;
                return;
            }

            string username = Common.FilterString(Common.GetStringOfForm("username"));
            //昵称可以输入任何字符，所以要对它进行HTML编码，防止恶意木马脚本字符串；过滤"'"为"''"，避免SQL注入式攻击
            string nickname = Server.HtmlEncode(Common.GetStringOfForm("nickname").Replace("'", "''"));
            string sex = Common.FilterString(Common.GetStringOfForm("sex"));
            string pwd = Common.FilterString(Common.GetStringOfForm("pwd"));//Common.FilterString( Common.GetStringOfForm( "hidPwd" ) );//
            string ejpwd ="";//Common.FilterString( Common.GetStringOfForm( "hidPwd2" ) );//
            string email ="";
            string mobile = Common.FilterString(Common.GetStringOfForm("mobile"));//电话保存到TUserInfo表的PhoneNum列
            string promoter = Common.FilterString(Common.GetStringOfForm("promoter"));
            string logoid = Common.FilterString(Common.GetStringOfForm("logoid"));
            string idcard = Common.FilterString(Common.GetStringOfForm("idcard"));
            string signDsc = Server.HtmlEncode(Common.GetStringOfForm("sign").Replace("'", "''"));
            string qqnum = "";
			string realname ="";
            if (string.IsNullOrEmpty(sex) || !CommonManager.String.IsInteger(sex))
                sex = "1";

            if (string.IsNullOrEmpty(logoid) || !CommonManager.String.IsInteger(logoid))
                logoid = "1";

            //新增：注册时选择职业和地区
            //string occu = CommonManager.Web.RequestForm( "txtOccuPation", "" );
            //string prov = CommonManager.Web.RequestForm( "hidProvince", "" );
            //string city = CommonManager.Web.RequestForm( "hidCity", "" );
            //string address = Server.HtmlEncode( CommonManager.Web.RequestForm( "txtAddress", "" ) );
            //如果银行密码为空，就把它设为登录密码
            if (ejpwd.Trim().Length == 0)
            {
                ejpwd = pwd;
            }

            BLL.Member member = new BLL.Member();
            int dbLogoId = member.SetLogoID(int.Parse(sex), int.Parse(logoid));
            /*
            string userId = Utility.SqlHelper.GetMaxID("UserID", "TUsers").ToString();

            //1.插入TUsers表
	
            member.Add2TUsers( userId, username, nickname, pwd, ejpwd, int.Parse( sex ), dbLogoId );

            //2.插入TUserInfo表
            int walletMoney = BLL.Config.GoldCountOfReg();
            BLL.Promotion promo = new BLL.Promotion();
            bool isTg = false;
            if( promoter.Trim().Length > 0 )
            {
                if( member.ExistName( promoter ) && promo.ExistTGUser( promoter ) )
                {
                    isTg = true;
                    walletMoney += BLL.Config.GoldCountOfRegTG();
                }
            }*/

            #region 增加判断是否在新手送礼包活动期间
            /*
        bool isaction = false;
        if (RookiePresentConfig.Config.IsEnable)
        {
            if (RookiePresentConfig.Config.BeginDate <= DateTime.Now && RookiePresentConfig.Config.EndDate >= DateTime.Now)
            {
                isaction = true;
                //walletMoney += RookiePresentConfig.Config.Money;
                //赠送道具
                if (RookiePresentConfig.Config.PropPresent.Rows.Count > 0)
                {
                    string select = "select Count(PropID) from TPropDefine where PropID=@PropID;";
                    string sql = "insert into TUserProp (UserID,PropID,HoldCount) values ({0},{1},{2});";
                    StringBuilder sqlCollection = new StringBuilder();
                    foreach (DataRow row in RookiePresentConfig.Config.PropPresent.Rows)
                    {
                        int tmpcount = DbSession.Default.FromSql(select).AddInputParameter("@PropID", DbType.Int32, row["PropID"]).ToScalar<int>();
                        if (tmpcount <= 0)
                            continue;
                        sqlCollection.AppendFormat(sql, userId, row["PropID"].ToString(), row["Amount"].ToString());
                    }
                    if (sqlCollection.ToString().Length > 0)
                    {
                        DbSession.Default.FromSql(sqlCollection.ToString()).Execute();
                    }
                }
            }
            else
            {
                isaction = false;
                RookiePresentConfig.Config.IsEnable = false;
                RookiePresentConfig.Save(RookiePresentConfig.Config);
            }
        }*/
            #endregion

            /*member.Add2TUserInfo(userId, walletMoney, Common.RequestIP);
		//修改为如下方法：
		//member.Add2TUserInfo( userId, walletMoney, Common.RequestIP, occu, prov, city, address, mobile );

		//3.插入Web_Users表
		member.Add2Web_Users(userId, email, mobile, Common.RequestIP, idcard);
		//member.Add2Web_Users( userId, email, "", Common.RequestIP );

		//4.插入推广日志信息
		if( isTg )
		{
			promo.AddLog( promoter, userId );
		}
		*/
			string agencyName = UiCommon.StringConfig.GetAgencyNameByTwoDname(); //获取域名获取代理商账号
            int userId =Convert.ToInt32(member.Add_UserInfo(username, nickname, promoter, int.Parse(sex), dbLogoId, pwd, ejpwd, idcard, mobile, email, Common.RequestIP, qqnum, realname,agencyName,signDsc)["UserID"]);
            if (userId > 0)
            {
                //5.保存用户信息
                UiCommon.UserLoginInfo.SetInfo(userId.ToString(), username);


                //更新用户登陆信息
                new BLL.Member().UpdateLastLogin(username, Utility.Common.RequestIP);

                //6.记录当前客户机器上的注册时间到cookies
                BCSTCache.Default.Save<CookiesCache>("RegDateTime", DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss"));


                //Limit.outMsgBox("温馨提示：\\n\\n会员注册成功！", "bzwp://regsucceed?username=" + SqlUsername + "", true);


                //Response.Write("<script language=javascript>window.alert('" + Message + "');" + str + "</script>");

                string ieEvent = "bzwp://regsucceed?username=" + username + "&userid=" + userId;
                Response.Write("<script language=javascript>window.location.href='" + ieEvent + "';</script>");
            }
            else
            {
                Label1.Text = "抱歉，注册失败，可能是服务器繁忙，请稍后再试！";
                return;
            }
            /*
            if (isaction)
            {
                Response.Write("<script language=javascript>alert('现在是活动期间，您获得系统赠送给您的道具！\\r\\n快到游戏的道具箱中去体验我们的道具吧！');window.location.href='" + ieEvent + "';</script>");
            }
            else
            {
                Response.Write("<script language=javascript>window.location.href='" + ieEvent + "';</script>");
            }
            */


        }
    }
}
