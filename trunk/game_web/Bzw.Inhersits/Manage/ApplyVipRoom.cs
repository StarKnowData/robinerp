using System;
using System.Collections.Generic;
using System.Text;
using Bzw.Data;
using System.Data;
using BCST.Common;
using System.Web.UI.WebControls;

namespace Bzw.Inhersits.Manage
{
      public partial class Manage_ApplyVipRoom:UiCommon.ManageBasePage
    {
        /// <summary>
        /// Head1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlHead Head1;

        /// <summary>
        /// webmeta1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webmeta1;

        /// <summary>
        /// webtop1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webtop1;

        /// <summary>
        /// leftOne 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl leftOne;

        /// <summary>
        /// webServiceOne 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webServiceOne;

        /// <summary>
        /// frmLogin 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.HtmlControls.HtmlForm frmLogin;

        /// <summary>
        /// lbMsg 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Label lbMsg;

        /// <summary>
        /// NameID 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.DropDownList NameID;

        /// <summary>
        /// hdBankMoney 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.HiddenField hdBankMoney;

        /// <summary>
        /// BuyDays 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.DropDownList BuyDays;

        /// <summary>
        /// Remark 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox Remark;

        /// <summary>
        /// txtValidCode 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.TextBox txtValidCode;

        /// <summary>
        /// Button1 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.WebControls.Button Button1;

        /// <summary>
        /// webFooter 控件。
        /// </summary>
        /// <remarks>
        /// 自动生成的字段。
        /// 若要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
        /// </remarks>
        protected global::System.Web.UI.UserControl webFooter;
        protected string username;
        protected string TaxType;



        protected void Page_Load(object sender, EventArgs e)
        {

            TaxType = UiCommon.StringConfig.RoomTaxSelected;
            if (UiCommon.UserLoginInfo.IsLogin)
                username = UiCommon.UserLoginInfo.UserName;
            else
                username = "";
            hdBankMoney.Value = (new BLL.Member().GetBankMoney(UiCommon.UserLoginInfo.UserID)).ToString();
            BindNameID();
            BindDay();

        }


        /// <summary>
        /// 绑定游戏名称
        /// </summary>
        private void BindNameID()
        {
            DataTable td = new DataTable();
            string sql = "select Nameid,ComName from TGameNameInfo where EveryDayRent >0 and Enable=1  order by EveryDayRent asc";
            td = DbSession.Default.FromSql(sql).ToDataTable();
            if (td.Rows.Count > 0)
            {
                this.NameID.DataSource = td;
                this.NameID.DataValueField = "Nameid";
                this.NameID.DataTextField = "ComName";
                this.NameID.DataBind();
                this.NameID.Items.Insert(0, new ListItem("请选择名称", ""));
            }
        }

        /// <summary>
        /// 租赁时长
        /// </summary>
        private void BindDay()
        {
            this.BuyDays.Items.Insert(0, new ListItem("请选择", ""));
            for (int i = 1; i < 31; i++)
            {
                this.BuyDays.Items.Insert(i, new ListItem(i.ToString(), i.ToString()));

            }

        }



        #region 提交申请
        protected void AddApplyVipRoom(object sender, EventArgs e)
        {

            if (!IsValid)
                return;
            if (!CommonManager.Web.CheckPostSource())
                return;
          
            //用户信息
            string sqlUserName, sqlLoginPsw, sqlEmail, sqlQQ, sqlMobile;
            //申请游戏信息
            string sqlGameName, sqlBuyDays, sqlBeginDate;
            //房间信息
            string sqlRoomName, sqlRoomPsw, strPsw2, sqlDeskNum, sqlMaxPeople, sqlSelTaxType, sqlTax, sqlBasePoint;
            //可选信息
            string sqlLessPoint, sqlMaxPoint, sqlRoomWelcome, sqlRallWelcome, sqlRemark;

          

            sqlLoginPsw = CommonManager.Web.RequestForm("LoginPsw", "");
            sqlEmail = CommonManager.Web.RequestForm("Email", "");
            sqlQQ = CommonManager.Web.RequestForm("QQ", "");
            sqlMobile = CommonManager.Web.RequestForm("Mobile", "");

            sqlGameName = CommonManager.Web.RequestForm("NameID", "");
            sqlBuyDays = CommonManager.Web.RequestForm("BuyDays", "");
            sqlBeginDate = CommonManager.Web.RequestForm("BeginDate", "");

            sqlRoomName = CommonManager.Web.RequestForm("RoomName", "");
            sqlRoomPsw = CommonManager.Web.RequestForm("RoomPsw", "");
            strPsw2 = CommonManager.Web.RequestForm("Psw2", "");
            sqlDeskNum = CommonManager.Web.RequestForm("DeskNum", "0");
            sqlMaxPeople = CommonManager.Web.RequestForm("MaxPeople", "0");
            sqlSelTaxType = CommonManager.Web.RequestForm("selTaxType", "");
            sqlTax = CommonManager.Web.RequestForm("txtTax", "");
            sqlBasePoint = CommonManager.Web.RequestForm("BasePoint", "");

            sqlLessPoint = CommonManager.Web.RequestForm("LessPoint", "0");
            sqlMaxPoint = CommonManager.Web.RequestForm("MaxPoint", "0");
            sqlRoomWelcome = CommonManager.Web.RequestForm("RoomWelcome", "");
            sqlRallWelcome = CommonManager.Web.RequestForm("RallWelcome", "");
            sqlRemark = CommonManager.Web.RequestForm("Remark", "");
            //不能在游戏中
            if ((new BLL.Member()).IsInRoomOrGame(UiCommon.UserLoginInfo.UserName))
            {
                RegJs("帐号正在游戏中，请先退出游戏再进行申请。", this.GetType(), Page); return;
                
            }
            //1. 验证必填项


            if (sqlLoginPsw.ToString() == "") { RegJs("请输入登录密码！", this.GetType(), Page); return; }
            if (sqlLoginPsw.ToString().Length > 20) { RegJs("登录密码最多20个字符", this.GetType(), Page); return; }

            if (sqlGameName.ToString() == "") { RegJs("请选择游戏名称！", this.GetType(), Page); return; }
            if (sqlBuyDays.Equals("")) { RegJs("请选择租凭房间时长", this.GetType(), Page); return; }
            if (!CommonManager.String.IsInteger(sqlBuyDays)) { RegJs("租凭房间时长只能为数字！", this.GetType(), Page); return; }
            if (sqlBuyDays.Equals("")) { RegJs("请选择租凭房间日期", this.GetType(), Page); return; }
            //if (!CommonManager.String.IsDateTime(sqlBuyDays)) { RegJs("租凭房间日期格式不正确，如：2012-08-15", this.GetType(), Page); return; }

            if (sqlRoomName.ToString() == "") { RegJs("请输入房间名称！", this.GetType(), Page); return; }
            if (sqlRoomName.ToString().Length > 12) { RegJs("房间名称最多12个字符", this.GetType(), Page); return; }
            if (strPsw2 != sqlRoomPsw) { RegJs("房间密码两次输入不一样，请重新输入", this.GetType(), Page); return; }
            if (!CommonManager.String.IsInteger(sqlDeskNum)) { RegJs("桌子数只能为数字！", this.GetType(), Page); return; }
            if (int.Parse(sqlDeskNum) < 0 || int.Parse(sqlDeskNum) > 45) { RegJs("桌子数只能大于0小于45！", this.GetType(), Page); return; }
            if (!CommonManager.String.IsInteger(sqlMaxPeople)) { RegJs("最大人数只能为数字！", this.GetType(), Page); return; }
            if (int.Parse(sqlMaxPeople) < 0 || int.Parse(sqlMaxPeople) > 180) { RegJs("最大人数只能大于0小于180！", this.GetType(), Page); return; }


            //2.校验验证码

            if (UiCommon.ValidCode.CurrentCode == null) { RegJs("验证码已过期，请输入新的验证码！", this.GetType(), Page); return; }
            else if (txtValidCode.Text.Trim() != UiCommon.ValidCode.CurrentCode) { RegJs("验证码输入错误，请输入新的验证码！", this.GetType(), Page); return; }


            //3. 验证用户名密码
            sqlUserName = UiCommon.UserLoginInfo.UserName;
            BLL.LoginResults lr = new BLL.Member().Login(sqlUserName, sqlLoginPsw);
            if (lr == BLL.LoginResults.PasswordInvalid) { RegJs("密码错误！", this.GetType(), Page); return; }
            else if (lr == BLL.LoginResults.Locked)
            {
                RegJs("您的帐号已经被管理员限制，不能登录！", this.GetType(), Page); return;
            }
            else if (lr == BLL.LoginResults.Succeed)
            {

                //4. 验证银行金币数
                //string sql = string.Empty;
                //BLL.RoomRent bll = new BLL.RoomRent();
                //long BankMony = bll.GetBankMoneyByUserName(sqlUserName);
                //int EveryDayRent = bll.GetEveryDayRent(int.Parse(sqlGameName));
                //int Days = int.Parse(sqlBuyDays);
                //long Chargeback = EveryDayRent * Days;

                //if (Chargeback > BankMony)
                //{
                //    RegJs("您的银行金币不够，请先充值，再重新申请，不便之处，敬请谅解！", this.GetType(), Page); return;
                //}
                //else
                //{
                    try
                    {
                        Dictionary<string, object> dic = new Dictionary<string, object>();
                        DbSession.Default.FromProc("Web_pApplyVipRoom")
                            .AddInputParameter("@UserID", DbType.Int32, UiCommon.UserLoginInfo.UserID)
                            .AddInputParameter("@UserName",DbType.String,UiCommon.UserLoginInfo.UserName)
                            .AddInputParameter("@Email",DbType.String,sqlEmail)
                            .AddInputParameter("@QQ", DbType.String, sqlQQ)
                            .AddInputParameter("@Mobile", DbType.String, sqlMobile)
                            .AddInputParameter("@ApplyGameNameID", DbType.String, sqlGameName)
                            .AddInputParameter("@OpenRoomDate", DbType.String, sqlBeginDate)
                            .AddInputParameter("@ApplyDays", DbType.String, sqlBuyDays)
                            .AddInputParameter("@RoomName", DbType.String, sqlRoomName)
                            .AddInputParameter("@RoomPwd", DbType.String, sqlRoomPsw)
                            .AddInputParameter("@DeskCount", DbType.String, sqlDeskNum)
                            .AddInputParameter("@TaxType", DbType.String, sqlSelTaxType)
                            .AddInputParameter("@Tax", DbType.String, sqlTax)
                            .AddInputParameter("@MaxPeople", DbType.String, sqlBasePoint)

                            .AddInputParameter("@BasePoint", DbType.String, sqlBasePoint)
                            .AddInputParameter("@LessPoint", DbType.String, sqlLessPoint)
                            .AddInputParameter("@MaxPoint", DbType.String, sqlMaxPoint)
                            .AddInputParameter("@RoomMsg", DbType.String, sqlRoomWelcome)
                            .AddInputParameter("@RallWelcome", DbType.String, sqlRallWelcome)
                            .AddInputParameter("@Remark", DbType.String, sqlRemark)
                            .AddReturnValueParameter("@ReturnValue", DbType.Int32)
                            .Execute();
                        if (dic.Count > 0)
                        {
                            string result = dic["ReturnValue"].ToString();
                            if (result == "-1")
                            {
                                RegJs("您的银行金币不足以租赁房间！", this.GetType(), Page); return;
                            }
                            
                        }
//                        sql = @"
//                        update TUserInfo set BankMoney=BankMoney-@Chargeback where UserID=@UserID;
//                        insert into Web_MoneyChangeLog(UserID,UserName,StartMoney,ChangeMoney,ChangeType,[DateTime],Remark ) 
//                        values(@UserID,@UserName,@SumMoney,@InMoney,28,getdate(),'申请房间租赁');
//                        insert into Web_ApplyVipRoom(UserID,Email,QQ,Mobile,ApplyGameNameID,
//                        OpenRoomDate,AppleyDays,RoomName,RoomPwd,DeskCount,TaxType,Tax,MaxPeople,
//                        BasePoint,LessPoint,MaxPoint,RoomMsg,RallWelcome,Remark,RoomID,AuditStatus)
//                        values(@UserID,@Email,@QQ,@Mobile,@ApplyGameNameID,
//                        @OpenRoomDate,@AppleyDays,@RoomName,@RoomPwd,@DeskCount,@TaxType,@Tax,@MaxPeople,
//                        @BasePoint,@LessPoint,@MaxPoint,@RoomMsg,@RallWelcome,@Remark,0,0);";

//                        DbSession.Default.FromSql(sql)
//                            .AddInputParameter("@UserID", DbType.String, UiCommon.UserLoginInfo.UserID)
//                            .AddInputParameter("@UserName", DbType.String, sqlUserName)
//                            .AddInputParameter("@SumMoney", DbType.String, BankMony)
//                            .AddInputParameter("@InMoney", DbType.String, (Chargeback * -1).ToString())
//                            .AddInputParameter("@Chargeback", DbType.String, Chargeback.ToString())
//                            .AddInputParameter("@Email", DbType.String, sqlEmail)
//                            .AddInputParameter("@QQ", DbType.String, sqlQQ)
//                            .AddInputParameter("@Mobile", DbType.String, sqlMobile)
//                            .AddInputParameter("@ApplyGameNameID", DbType.String, sqlGameName)
//                            .AddInputParameter("@OpenRoomDate", DbType.String, sqlBeginDate)
//                            .AddInputParameter("@AppleyDays", DbType.String, sqlBuyDays)

//                            .AddInputParameter("@RoomName", DbType.String, sqlRoomName)
//                            .AddInputParameter("@RoomPwd", DbType.String, sqlRoomPsw)
//                            .AddInputParameter("@DeskCount", DbType.String, sqlDeskNum)
//                            .AddInputParameter("@TaxType", DbType.String, sqlSelTaxType)
//                            .AddInputParameter("@Tax", DbType.String, sqlTax)
//                            .AddInputParameter("@MaxPeople", DbType.String, sqlBasePoint)

//                            .AddInputParameter("@BasePoint", DbType.String, sqlBasePoint)
//                            .AddInputParameter("@LessPoint", DbType.String, sqlLessPoint)
//                            .AddInputParameter("@MaxPoint", DbType.String, sqlMaxPoint)
//                            .AddInputParameter("@RoomMsg", DbType.String, sqlRoomWelcome)
//                            .AddInputParameter("@RallWelcome", DbType.String, sqlRallWelcome)
//                            .AddInputParameter("@Remark", DbType.String, sqlRemark)

//                            .Execute();

                        RegJs("申请成功，请等待审核！", this.GetType(), Page); return;
                    }
                    catch
                    {
                        RegJs("未知错误，请与客服联系！", this.GetType(), Page); return;
                    }

                //}
            }
        }
        #endregion
 

        /// <summary>
        /// aspx页面注册JAVASCRIPT
        /// </summary>
        /// <param name="str"></param>
        /// <param name="cstype"></param>
        private void RegJs(string str, Type cstype, System.Web.UI.Page page)
        {
            String s = "<script>";
            s += "alert('" + str.Trim() + "');" + "<" + "/" + "script>";
            //Type cstype = this.GetType();
            String csname1 = "PopupScript";
            System.Web.UI.ClientScriptManager cs = page.ClientScript;
            if (!cs.IsStartupScriptRegistered(cstype, csname1))
            {
                cs.RegisterStartupScript(cstype, csname1, s, false);
            }
        }

    }
}
