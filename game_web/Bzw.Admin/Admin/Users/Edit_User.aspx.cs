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
using System.Text;
using System.Globalization;

public partial class Admin_Users_Edit_User : AdminBasePage
{
	/// <summary>
	/// 页面传递的id参数，用户id
	/// </summary>
	protected int UserID
	{
		get
		{
			string tmp = CommonManager.Web.Request( "id", "" );
			if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
				return 0;
			return int.Parse( tmp );
		}
	}

	public string needqq = System.Configuration.ConfigurationSettings.AppSettings["qq"];
	public string userName = string.Empty;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "04" );

		string isTrader = ConfigurationManager.AppSettings["IsOpenTrader"];
		if( isTrader == "0" )
		{
			trIsTrader.Visible = false;
		}
		if( UserID == 0 )
		{
			CommonManager.Web.RegJs( this, "alert('参数错误。');", false );
			return;
		}

		if( IsPostBack )
			return;

		string sql = @"select *,DATEADD([second],viptime,'1970-1-1 8:00:00') AS VipTimes,(select isnull(Convert(bigint,sum(ChangeTax)),0) as tax from TChangeRecordUser where UserID=@UserID) as AllTax from TUsers a inner join TUserInfo b on b.UserID=a.UserID inner join Web_Users c on c.UserID=a.UserID where a.UserID=@UserID";

		DataTable dt = DbSession.Default.FromSql( sql ).AddInputParameter( "@UserID", DbType.Int32, UserID ).ToDataTable();

		if( dt.Rows.Count <= 0 )
		{
			CommonManager.Web.RegJs( this, "alert('参数错误。');", false );
			return;
		}

		DataRow row = dt.Rows[0];

		#region 填充页面表单
		if( row["LockMathine"].ToString() == "1" )
		{
			lockLB.Visible = true;
			LockLabel.Text = "已锁定";
		}
		else
		{
			LockLabel.Text = "未锁定";
		}
		txtBankMoney.Text = row["BankMoney"].ToString();
		txtFascination.Text = row["Fascination"].ToString();
		txtNickName.Text = row["NickName"].ToString();
		//LiteralNickName.Text = row["NickName"].ToString();
		txtPwd_anw.Text = row["Pwd_anw"].ToString();
		ltPwd_ques.Text = row["Pwd_ques"].ToString();
		//txtUserNames.Text = row["UserName"].ToString();
		LiteralUserName.Text = row["UserName"].ToString();
        if (UiCommon.StringConfig.BankVersion == "1")
        {
            txtWalletMoney.Text = row["WalletMoney"].ToString();
        }
        else
        {
            txtWalletMoney.Text = (new BLL.Member()).GetWalletMoney(UserID.ToString()).ToString();
            txtWalletMoney.ReadOnly = true;
        }
		txtZJ_Number.Text = row["ZJ_Number"].ToString();
		CommonManager.Web.SetListControlSelectedFromValue( ddlMaster, row["Master"].ToString() );
		CommonManager.Web.SetListControlSelectedFromValue( ddlMember, row["Member"].ToString() );
		CommonManager.Web.SetListControlSelectedFromValue( ddlUserType, row["UserType"].ToString() );
		CommonManager.Web.SetListControlSelectedFromValue( ddlZJ_Type, row["ZJ_type"].ToString() );
		CommonManager.Web.SetListControlSelectedFromValue( rdolDisabled, row["Disabled"].ToString() );
		CommonManager.Web.SetListControlSelectedFromValue( rdolSex, row["Sex"].ToString() );
		CommonManager.Web.SetListControlSelectedFromValue( rdoIsTrader, row["Trader"].ToString() );
        ltSignDesc.Text = row["SignDescr"].ToString();
        ltAddress.Text = row["Address"].ToString();
        ltTelNo.Text = row["TelNo"].ToString();
		//ltAdrCity.Text = row["AdrCity"].ToString();
		//ltAdrProvince.Text = row["AdrProvince"].ToString();
		//ltAdrZone.Text = row["AdrZone"].ToString();
		ltAllLoginTime.Text = row["AllLoginTime"].ToString();
		ltCurrentVIPTime.Text = row["VipTimes"].ToString();
		ltEmail.Text = row["Email"].ToString();
		ltqqnum.Text = row["qqnum"].ToString();
		//设置头像图片显示
		int Sex = Convert.ToInt32(row["Sex"]);
		int LogoID = (int)row["LogoID"];
		LogoID = new BLL.Member().GetLogoID(Sex, LogoID);
		string UserHeadImg = "";
        if (LogoID >= BLL.Member.LogoId_Const1 && LogoID <= BLL.Member.LogoId_Const2)
        {
            if (row["Sex"].ToString() == "1")
            {
                UserHeadImg = "/Image/Users/b_" + LogoID + ".png";
            }
            else
            {
                UserHeadImg = "/Image/Users/g_" + LogoID + ".png";
            }
        }
		else if( LogoID >= BLL.Member.LogoId_Const3 && LogoID <= BLL.Member.LogoId_Const4 ) //上传的自定义头像 256<=LogoID<=512
		{
			int childDirName = UserID / 1000;
			UserHeadImg = "/Upload/" + UiCommon.StringConfig.UserCustHeadFolderName + "/" + childDirName + "/" + UserID + ".png";
		}
		else if( LogoID > BLL.Member.LogoId_Const4 ) //上传的自定义头像 LogoID>512  需审核或有过期时间的自定义头像
		{
			int childDirName = UserID / 1000;
			UserHeadImg = "/Upload/" + UiCommon.StringConfig.UserCustHeadFolderName + "/" + childDirName + "/" + UserID + ".png";
		}
		ltHeadImg.Text = "<img src='" + UserHeadImg + "' onerror='this.src=\"/images/NoPicture/no_pic.gif\";this.onerror=\"\";' />";

		ltLastLoginIP.Text = row["LastLoginIP"].ToString();
		ltLastLoginTM.Text = ( (DateTime)row["LastLoginTM"] ).ToString( "yyyy-MM-dd HH:mm:ss" );
		//ltOccuPation.Text = row["OccuPation"].ToString();
		ltPhoneNum.Text = row["Phone"].ToString();
		ltRegisterIP.Text = row["RegisterIP"].ToString();
		ltRegisterTM.Text = ( (DateTime)row["RegisterTM"] ).ToString( "yyyy-MM-dd HH:mm:ss" );
		ltUserName.Text = row["UserName"].ToString();
		userName = row["UserName"].ToString();
		//ltWebLoginTime.Text = row["WebLoginTime"].ToString();

		ltSourcePwd.Text = row["Pass"].ToString();
		ltSourceTwoPwd.Text = row["TwoPassword"].ToString();

		ltAllTax.Text = row["AllTax"].ToString();
		txtUserRealName.Text = row["RealName"].ToString();
        txtLotteries.Text = row["Lotteries"].ToString();
        if (row["Disabled"].ToString() == "1")
        {
            txtBankMoney.Enabled = false;
            txtWalletMoney.Enabled = false;
            rdolVip.Enabled = false;
            txtCustomVIP.Enabled = false;
        }
		#endregion
	}

	protected void Edit_Users( object sender, EventArgs e )
	{
		if( !CommonManager.Web.CheckPostSource() )
			return;

		if( UserID == 0 )
			return;
		DataRow row = new BLL.Member().GetInfo( UserID.ToString() );
		if( row == null )
			return;

		using( DbTrans trans = DbSession.Default.BeginTrans() )
		{
			try
			{
				#region 对TUsers表的修改
                if (txtNickName.Text.Trim() == "")
                {
                    CommonManager.Web.RegJs(this, "alert('昵称不能为空！');location.href=location.href;", false);
                    return;
                }
                string nickName = txtNickName.Text.Trim();
				StringBuilder sql = new StringBuilder( "update TUsers set " );
				sql.Append( " Sex=@Sex," );
				sql.Append( " Disabled=@Disabled," );
                sql.Append(" NickName=@NickName ");  
				if( !string.IsNullOrEmpty( txtPassWord.Text.Trim() ) )
					sql.Append( " ,Pass=@Password" );
				if( !string.IsNullOrEmpty( txtTwoPassWord.Text.Trim() ) )
					sql.Append( " ,TwoPassword=@TwoPassword" );
				sql.Append( " where UserID=@UserID;" );

				SqlSection sect = trans.FromSql( sql.ToString() )
					.AddInputParameter( "@Sex", DbType.Int16, rdolSex.SelectedItem.Value )
					.AddInputParameter( "@Disabled", DbType.Int32, rdolDisabled.SelectedItem.Value )
					.AddInputParameter( "@UserID", DbType.Int32, UserID )
                    .AddInputParameter("@NickName", DbType.Int32, nickName);
                    

				if( !string.IsNullOrEmpty( txtPassWord.Text.Trim() ) )
                    sect.AddInputParameter("@Password", DbType.String, Utility.Common.md5(txtPassWord.Text.Trim())/*CommonManager.String.EncryptMD5SystemDefaultMethod(txtPassWord.Text.Trim(),false,true)*/ );

				if( !string.IsNullOrEmpty( txtTwoPassWord.Text.Trim() ) )
                    sect.AddInputParameter("@TwoPassword", DbType.String, Utility.Common.md5(txtTwoPassWord.Text.Trim()) /*CommonManager.String.EncryptMD5SystemDefaultMethod( txtTwoPassWord.Text.Trim(), false, true )*/ );

				sect.Execute();
				#endregion

				#region 判断是否需要修改TMatchTable
				if( row["Master"].ToString() != ddlMaster.SelectedItem.Value )
				{
					sql = new StringBuilder();
					if( ddlMaster.SelectedItem.Value == "3" )
					{
						sql.Append( "update TMatchTable set MasterPower=268435455 where UserID=@UserID;" );
					}
					else if( ddlMaster.SelectedItem.Value == "0" )
					{
						sql.Append( "update TMatchTable set MasterPower=0 where UserID=@UserID;" );
					}
					trans.FromSql( sql.ToString() ).AddInputParameter( "@UserID", DbType.Int32, UserID ).Execute();
				}
				#endregion

				#region 计算VIP时间
				int addvip = (int)row["VipTime"];//得到原来的时间，秒数
				
				if( rdolVip.SelectedIndex != -1 || ( !string.IsNullOrEmpty( txtCustomVIP.Text.Trim() ) ) )
				{
					
					int tmp = 0;
					if( rdolVip.SelectedIndex != -1 )//预设值优先
					{
						tmp = int.Parse( rdolVip.SelectedItem.Value );
					}
					else
					{
						if (!CommonManager.String.IsInteger(txtCustomVIP.Text.Trim()))
						{
							CommonManager.Web.RegJs(this, "alert('自定义天数必须为数字！');location.href=location.href;", false);
							return;
						}
						tmp = ( int.Parse( txtCustomVIP.Text.Trim() ) * 24 * 3600 );
					}

					//如果不是取消vip，则补齐时间差
					if( tmp > 0 )
					{
						DateTime curVIP = (DateTime)row["VipTime2"];//得到原来时间的DateTime格式
						if( curVIP == new DateTime( 1970, 1, 1, 8, 0, 0 ) )
						{
							//从未设置过vip时间，则用当前时间与初始时间的时间差加上要增加的时间。
							addvip = (int)( DateTime.Now - new DateTime( 1970, 1, 1, 8, 0, 0 ) ).TotalSeconds + tmp;
						}
						else if( curVIP < DateTime.Now )
						{
							//有过vip，但已到期，则补齐时间差
							addvip += (int)( DateTime.Now - curVIP ).TotalSeconds + tmp;
						}
						else
						{
							//有vip，且未到期，则在原来基础上增加
							addvip += tmp;
						}
					}
					else
					{
						//取消vip
						addvip = 0;
					}
				}
				#endregion

                Int64 mon;
                Int64 bmon;

				#region 判断是否需要插入金币修改表
				if (!Int64.TryParse( txtWalletMoney.Text.Trim(),out mon))
				{
					CommonManager.Web.RegJs(this, "alert('钱包金币数必须为数字,或超出整数范围');location.href=location.href;", false);
					return;
				}
                if (!Int64.TryParse(txtBankMoney.Text.Trim(),  out bmon))
				{
                    CommonManager.Web.RegJs(this, "alert('银行金币数必须为数字，或超出整数范围');location.href=location.href;", false);
					return;
				}
				if (!CommonManager.String.IsInteger(txtFascination.Text.Trim()))
				{
					CommonManager.Web.RegJs(this, "alert('魅力数必须为数字！');location.href=location.href;", false);
					return;
				}
				string newWM = string.IsNullOrEmpty( txtWalletMoney.Text.Trim() ) ? "0" : txtWalletMoney.Text.Trim();
				string newBM = string.IsNullOrEmpty( txtBankMoney.Text.Trim() ) ? "0" : txtBankMoney.Text.Trim();

				#region Old code
				/*
				if( row["WalletMoney"].ToString() != newWM )
				{
					sql = new StringBuilder();
					sql.Append( "insert into Web_MoneyChangeLog (userid,username,frontmoney,aftermoney,changetype,addtime,adduser)" );
					sql.Append( " values (@UserID,@UserName,@OldWalletMoney,@WalletMoney,0,getdate(),@AdminName);" );

					trans.FromSql( sql.ToString() )
							.AddInputParameter( "@UserID", DbType.Int32, UserID )
							.AddInputParameter( "@UserName", DbType.String, row["UserName"].ToString() )
                            .AddInputParameter("@OldWalletMoney", DbType.Int32, row["WalletMoney"])
                            .AddInputParameter("@WalletMoney", DbType.Int32, newWM)
							.AddInputParameter( "@AdminName", DbType.Int16, AdminInfo["UserName"].ToString() )
							.Execute();
					//int dvalue = int.Parse( newWM ) - (int)row["WalletMoney"];
					//if( dvalue > 0 )
					//{
					//    MoneyOperator.Default.Add_Web_Record_MoneyIncrease( dvalue, Session["AdminName"].ToString() + "管理员手动给玩家" + row["UserName"].ToString() + "添加钱包金币" );
					//}
					//else
					//{
					//    MoneyOperator.Default.Add_Web_Record_MoneyDecrease( Math.Abs( dvalue ), Session["AdminName"].ToString() + "管理员手动减去玩家" + row["UserName"].ToString() + "钱包金币" );
					//}
				}
				if( row["BankMoney"].ToString() != newBM )
				{
					sql = new StringBuilder();
					sql.Append( "insert into Web_MoneyChangeLog (userid,username,frontmoney,aftermoney,changetype,addtime,adduser)" );
					sql.Append( " values (@UserID,@UserName,@OldBankMoney,@BankMoney,0,getdate(),@AdminName);" );

					trans.FromSql( sql.ToString() )
							.AddInputParameter( "@UserID", DbType.Int32, UserID )
							.AddInputParameter( "@UserName", DbType.String, row["UserName"].ToString() )
                            .AddInputParameter("@OldBankMoney", DbType.Int32, row["WalletMoney"])
                            .AddInputParameter("@BankMoney", DbType.Int32, newBM)
							.AddInputParameter( "@AdminName", DbType.Int16, AdminInfo["UserName"].ToString() )
							.Execute();

					//int dvalue = int.Parse( newBM ) - (int)row["BankMoney"];
					//if( dvalue > 0 )
					//{
					//    MoneyOperator.Default.Add_Web_Record_MoneyIncrease( dvalue, Session["AdminName"].ToString() + "管理员手动给玩家" + row["UserName"].ToString() + "添加银行金币" );
					//}
					//else
					//{
					//    MoneyOperator.Default.Add_Web_Record_MoneyDecrease( Math.Abs( dvalue ), Session["AdminName"].ToString() + "管理员手动减去玩家" + row["UserName"].ToString() + "银行金币" );
					//}
				 
				}
				*/
				#endregion

				if( row["WalletMoney"].ToString() != newWM || row["BankMoney"].ToString() != newBM )	//如果修改金币，则插入金币变化日志
				{
					Int64 startMoney = Convert.ToInt64( row["WalletMoney"] ) + Convert.ToInt64( row["BankMoney"] );
					Int64 changeMoney = ( Convert.ToInt64( newWM ) + Convert.ToInt64( newBM ) ) - startMoney;		
					string remark = ChineseMessage.adminManageNameMessage + AdminUserName + " " + ChineseMessage.adminManageIdMessage + AdminUserID;
					BLL.Member.WriteMoneyExChangeLog( UserID.ToString(), startMoney, changeMoney, (int)Library.MoneyChangeType.管理员修改金币, remark );
				}

				#endregion

				#region 对TUserInfo表的修改
				sql = new StringBuilder();
				sql.Append( "update TUserInfo set " );
				sql.Append( " Member=@Member," );
				sql.Append( " Master=@Master," );
				sql.Append( " WalletMoney=@WalletMoney," );
				sql.Append( " BankMoney=@BankMoney," );
				sql.Append( " Fascination=@Fascination," );
				sql.Append( " Viptime=@Viptime," );
				sql.Append( " UserType=@UserType," );
				sql.Append( " Trader=@Trader" );
				sql.Append( " where UserID=@UserID;" );
				trans.FromSql( sql.ToString() )
						.AddInputParameter( "@Member", DbType.Int32, ddlMember.SelectedItem.Value )
						.AddInputParameter( "@Master", DbType.Int32, ddlMaster.SelectedItem.Value )
						.AddInputParameter( "@WalletMoney", DbType.Int32, newWM )
						.AddInputParameter( "@BankMoney", DbType.Int32, newBM )
						.AddInputParameter( "@Fascination", DbType.Int32, string.IsNullOrEmpty( txtFascination.Text.Trim() ) ? "0" : txtFascination.Text.Trim() )
						.AddInputParameter( "@UserType", DbType.Int32, ddlUserType.SelectedItem.Value )
						.AddInputParameter( "@Viptime", DbType.Int32, addvip )
						.AddInputParameter( "@Trader", DbType.Int32, rdoIsTrader.SelectedValue)
						.AddInputParameter( "@UserID", DbType.Int32, UserID )
						.Execute();
				#endregion

				#region 对Web_Users表的修改
                if (!CommonManager.String.IsInteger(txtLotteries.Text.Trim()))
                {
                    CommonManager.Web.RegJs(this, "alert('"+UiCommon.StringConfig.GoldName+"数必须为数字！');location.href=location.href;", false);
                    return;
                }
				sql = new StringBuilder();
				sql.Append( "update Web_Users set " );
				sql.Append( " Pwd_anw=@Pwd_anw," );
				//sql.Append( " Pwd_ques=@Pwd_ques," );
				sql.Append( " ZJ_type=@ZJ_type," );
				sql.Append( " ZJ_Number=@ZJ_Number," );
				sql.Append( "RealName=@RealName," );
                sql.Append(" Lotteries=@Lotteries ");
				sql.Append( " where UserID=@UserID;" );
				

				trans.FromSql( sql.ToString() )
						.AddInputParameter( "@Pwd_anw", DbType.String, txtPwd_anw.Text.Trim() )						
						.AddInputParameter( "@ZJ_Number", DbType.String, txtZJ_Number.Text.Trim() )
						.AddInputParameter( "@ZJ_type", DbType.Int16, ddlZJ_Type.SelectedItem.Value )
						.AddInputParameter("@RealName",DbType.String,txtUserRealName.Text.Trim())
                        .AddInputParameter("@Lotteries",DbType.Int32,txtLotteries.Text.Trim())
						.AddInputParameter( "@UserID", DbType.Int32, UserID )
						.Execute();
				#endregion

				trans.Commit();

				CommonManager.Web.RegJs( this, "alert('修改成功！');location.href=location.href;", false );
			}
			catch( Exception ex )
			{
				trans.Rollback();
				CommonManager.Web.RegJs( this, "alert('发生错误，错误信息：" + ex.Message + "。\\r\\n未对数据库进行任何操作。');location.href=location.href;", false );
			}
		}
	}

	protected void LinkButton1_Click( object sender, EventArgs e )
	{
		string sqltext = "update TUserInfo set LockMathine='0',MathineCode=null where UserID="+UserID+"";
		DbSession.Default.FromSql( sqltext ).Execute();
		CommonManager.Web.RegJs( this, "alert('恭喜您，解除机器锁定成功');location.href=location.href", false );
	}
}
