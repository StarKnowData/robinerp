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
using System.Collections.Generic;
using BCST.Cache;
using BLL;
using System.Text;
using System.Management;
namespace Bzw.Inhersits.Manage
{
    public partial class Manage_Reg : UiCommon.BasePage
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
        /// webservice1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webservice1;

        /// <summary>
        /// frmLogin 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlForm frmLogin;

        /// <summary>
        /// btnSubmit 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlInputSubmit btnSubmit;

        /// <summary>
        /// webfooter1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webfooter1;

        public string needqq;
        public string needrealname;
        public string needIDCard;
        public string needProcted;
        protected void Page_Load(object sender, EventArgs e)
        {
            //获取注册的时候QQ,真实姓名,身份证号码是否为必添
            needqq = System.Configuration.ConfigurationSettings.AppSettings["QQ"];
            needrealname = System.Configuration.ConfigurationSettings.AppSettings["RealName"];
            needIDCard = System.Configuration.ConfigurationSettings.AppSettings["IDCard"];
            needProcted = System.Configuration.ConfigurationSettings.AppSettings["IsCardProtected"];//是否需要验证是否成年
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
                    //CommonManager.Web.RegJs( this, "alert('您的IP段在被限制的范围内，不能进行注册，请联系我们的客服进行咨询。');history.back;", false );
                    //return;
                    Response.Write("您的IP段在被限制的范围内，不能进行注册，请联系我们的客服进行咨询。");
                    Response.End();
                }
            }
           
            object lastRegDate = BCSTCache.Default.Get<CookiesCache>("RegDateTime");
            if (lastRegDate != null && CommonManager.String.IsDateTime(lastRegDate.ToString()))
            {
                if ((DateTime.Now - DateTime.Parse(lastRegDate.ToString())).TotalMinutes < timespan)
                {
                    //CommonManager.Web.RegJs( this, "alert('请不要重复注册。');history.back;", false );
                    //return;
                    Response.Write("请不要重复注册。");
                    Response.End();
                }
            }
            //同IP每天注册的用户数限制
            int MaxReg = (int)dt.Rows[0]["SameIPRegCount"];
            if (MaxReg > 0)
            { 
                //如果限制
                int UserCount =(int) DbSession.Default.FromSql("select COUNT(1) FROM dbo.Web_Users WHERE RegisterIP='"+userip+"'").ToScalar();
                if (UserCount >= MaxReg)
                {
                    //Response.Write("您的IP今日注册人数已达到限制数。");
                    //Response.End();
                    CommonManager.Web.RegJs(this, "alert('您的IP今日注册人数已达到限制数。');location.href='/Default.aspx';", false);
                    return;
                }
            }

            //先不要从表中根据ip读取时间进行限制。
            /*if( lastRegDate == null || !CommonManager.String.IsDateTime( lastRegDate.ToString() ) )
            {
                //查询同一ip在限制时间内是否有用户注册记录，以及注册时间
                DateTime? d = DbSession.Default.FromSql( "select RegisterTM from Web_Users where RegisterIP=@RegIP" ).AddInputParameter( "@RegIP", DbType.String, userip ).ToScalar<DateTime?>();
                if( d.HasValue && ( ( DateTime.Now - d.Value ).TotalMinutes < timespan * 60 ) )
                {
                    CommonManager.Web.RegJs( this, "alert('请不要重复注册。');history.back;", false );
                    return;
                }
            }
            else
            {
                if( ( DateTime.Now - DateTime.Parse( lastRegDate.ToString() ) ).TotalMinutes < timespan * 60 )
                {
                    CommonManager.Web.RegJs( this, "alert('请不要重复注册。');history.back;", false );
                    return;
                }
            }*/
        }
        protected void btnSubmit_ServerClick(object sender, EventArgs e)
        {
            string validcode = Common.GetStringOfForm("validcode");
            if (ValidCode.CurrentCode != validcode)
            {
                /*Label1.Text = "温馨提示：验证码输入错误，请重新输入！";
                Label1.Visible = true;*/
                CommonManager.Web.RegJs(this, "alert('温馨提示：验证码输入错误，请重新输入！');location.href=location.href;", true);
                return;
            }

            string username = Common.FilterString(Common.GetStringOfForm("username"));
            //昵称可以输入任何字符，所以要对它进行HTML编码，防止恶意木马脚本字符串；过滤"'"为"''"，避免SQL注入式攻击
            string nickname = Server.HtmlEncode(Common.GetStringOfForm("nickname").Replace("'", "''"));
            string sex = Common.FilterString(Common.GetStringOfForm("sex"));
            string pwd = Common.FilterString(Common.GetStringOfForm("pwd"));//Common.FilterString(Common.GetStringOfForm("pwd"));
            string ejpwd = Common.FilterString(Common.GetStringOfForm("ejpwd"));//Common.FilterString(Common.GetStringOfForm("ejpwd"));
            string email = Common.FilterString(Common.GetStringOfForm("email"));
            string mobile = Common.FilterString(Common.GetStringOfForm("mobile"));//电话保存到TUserInfo表的PhoneNum列
            string promoter = Common.FilterString(Common.GetStringOfForm("promoter"));
            string logoid = Common.FilterString(Common.GetStringOfForm("hidLogoID"));
            string idcard = Common.FilterString(Common.GetStringOfForm("idcard"));
            string qqNum = Common.FilterString(Common.GetStringOfForm("qqnum"));
            string realname = Common.FilterString(Common.GetStringOfForm("realname"));
            if (string.IsNullOrEmpty(sex) || !CommonManager.String.IsInteger(sex))
            {
                sex = "1";
            }
            if (string.IsNullOrEmpty(logoid) || !CommonManager.String.IsInteger(logoid))
            {
                logoid = "1";
            }

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


          

            //2012-12-16 根据域名来获取代理商ID，域名设置在代理商资料修改中
            string agencyName = UiCommon.StringConfig.GetAgencyNameByTwoDname(); //获取域名获取代理商账号



            int userId = Convert.ToInt32(member.Add_UserInfo(username, nickname, promoter, int.Parse(sex), dbLogoId, pwd, ejpwd, idcard, mobile, email, Common.RequestIP, qqNum, realname, agencyName)["UserID"]);
            if (userId > 0)
            {
                //5.保存用户信息
                UiCommon.UserLoginInfo.SetInfo(userId.ToString(), username);

                //更新用户登陆信息
                new BLL.Member().UpdateLastLogin(username, Utility.Common.RequestIP);

                //6.记录当前客户机器上的注册时间到cookies
                BCSTCache.Default.Save<CookiesCache>("RegDateTime", DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss"));
                Response.Redirect("/Manage/Default.aspx");
            }
            //else if (userId == -3)
            //{
            //    CommonManager.Web.RegJs(this, "alert('抱歉，注册失败，此IP今天注册人数已满！');location.href=location.href;", true);
            //}
            //else if (userId == -4)
            //{
            //    CommonManager.Web.RegJs(this, "alert('抱歉，注册失败，此身份证号已达到注册次数限制！');location.href=location.href;", true);
            //}
            else
            {
                CommonManager.Web.RegJs(this, "alert('抱歉，注册失败，可能是服务器繁忙，请稍后再试！');location.href=location.href;", true);
            }


        }
      
    }
}
