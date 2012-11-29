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
using Bzw.WebLibrary;

namespace Bzw.Inhersits
{
	public partial class DuiJiang : UiCommon.ManageBasePage
	{
		/// <summary>
		/// Head1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。s
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
		/// webshortcutkey1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		//protected global::Public_WebShortCutKey webshortcutkey1;

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
		/// txtTrueName 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.TextBox txtTrueName;

		/// <summary>
		/// txtPhone 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.TextBox txtPhone;

		/// <summary>
		/// RequiredFieldValidator2 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.RequiredFieldValidator RequiredFieldValidator2;

		/// <summary>
		/// RegularExpressionValidator1 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.RegularExpressionValidator RegularExpressionValidator1;

		/// <summary>
		/// txtAddress 控件。
		/// </summary>
		/// <remarks>
		/// 自动生成的字段。
		/// 要进行修改，请将字段声明从设计器文件移到代码隐藏文件。
		/// </remarks>
		protected global::System.Web.UI.WebControls.TextBox txtAddress;

		protected global::System.Web.UI.WebControls.TextBox txtUserRemark;

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

		public string AwardID = "0";
		public string AwardName = string.Empty;
		public string AwardPic = string.Empty;
		public Int64 AwardMoney = 0;
		public int AwardTime = 0;
		public int AwardCount = 0;
		public string AwardInfo = string.Empty;

		BLL.Member member = new BLL.Member();

		protected void Page_Load( object sender, EventArgs e )
		{
            SeoSetting(SeoConfig.Config.PrizeSeo);
			BindJiangPin();
		}

		public void BindJiangPin()
		{
			AwardID = Common.SqlEncode( Common.GetStringOfUrl( "id" ) );
			if( string.IsNullOrEmpty( AwardID ) || !CommonManager.String.IsInteger( AwardID ) )
			{
				Response.Write( "<script>alert('请不要尝试非法操作。');history.back();</script>" );
				Response.End();
				return;
			}

			DataRow dr = new BLL.JiangPin().GetInfo( AwardID );
			if( dr != null )
			{
				AwardName = dr["Award_Name"].ToString();
				AwardPic = dr["Award_Pic"].ToString();
				AwardMoney = Convert.ToInt64( dr["Award_MoneyCost"] );
				AwardTime = Convert.ToInt32( dr["Award_OnLineTime"] );
				AwardCount = Convert.ToInt32( dr["Award_Num"] );
				AwardInfo = dr["Award_Info"].ToString();
			}
			else
			{
				Response.Write( "<script>alert('您所查看的奖品，不存在或已被删除！');history.back();</script>" );
				Response.End();
				return;
			}

			//您所查看的奖品，不存在或已被删除！
		}

		protected void button5_ServerClick( object sender, EventArgs e )
		{
			//1.此奖品已兑换完毕
			if( AwardCount <= 0 )
			{
				/*lblMsg.Text = "抱歉，此奖品已兑换完毕！";
				*/
				CommonManager.Web.RegJs( this, "alert('抱歉，此奖品已兑换完毕！');location.href=location.href;", true );
				return;
			}

			//2.您有效的总游戏时间不够兑换此奖品！
			//int playTimeSum = Convert.ToInt32(member.GetPlayTimeSum(UserLoginInfo.UserID)); //秒
			int playTimeSum = Convert.ToInt32( member.GetAllPlayTimeByUserID( UserLoginInfo.UserID ) ); //秒
			int usedPlayTime = member.GetUsedPlayTimeOfJP( UserLoginInfo.UserID ) * 60 * 60;
			int awardTimes = AwardTime * 60 * 60;
			if( ( playTimeSum - usedPlayTime ) < awardTimes )
			{
				/*lblMsg.Text = "抱歉，您有效的总游戏时间不够兑换此奖品！";
				*/
				CommonManager.Web.RegJs( this, "alert('抱歉，您有效的总游戏时间不够兑换此奖品！');location.href=location.href;", true );
				return;
			}

			//3.您银行的金币不够兑换此奖品！
            //Int64 userBankMoney = member.GetBankMoney( UserLoginInfo.UserID );
            //if( userBankMoney < AwardMoney )
            //{
            //    /*lblMsg.Text = "抱歉，您银行的金币不够兑换此奖品！";
            //   */
            //    CommonManager.Web.RegJs( this, "alert('抱歉，您的"+ UiCommon.StringConfig.GoldName +"数不够兑换此奖品！');location.href=location.href;", true );
            //    return;
            //}

			//4.兑换
			string trueName = Common.FilterString( txtTrueName.Text );
			string phone = Common.FilterString( txtPhone.Text );
			string address = Common.FilterString( txtAddress.Text );
			string remark = Common.FilterString( txtUserRemark.Text );
	        //long summMoney = member.GetAllMoney( UserLoginInfo.UserID );
            //int iRows = member.DuiJiang( AwardID, UserLoginInfo.UserID, AwardMoney, AwardTime, trueName, phone, address, remark);
            //if( iRows > 0 )
            //{
            //    BLL.Member.WriteMoneyExChangeLog( UserLoginInfo.UserID, summMoney, -AwardMoney, (int)Library.MoneyChangeType.兑换奖品, "" );
            //    CommonManager.Web.RegJs( this, "alert('" + ConfigurationManager.AppSettings["DuiJingMgs"] + "');location.href=location.href;", true );
            //    /*lblMsg.Text = "奖品兑换成功！" + DateTime.Now;
            //    BindJiangPin();
            //    txtTrueName.Text = string.Empty;
            //    txtPhone.Text = string.Empty;
            //    txtAddress.Text = string.Empty;*/
            //}
            //else
            //{
            //    //lblMsg.Text = "抱歉，奖品兑换失败，可能是服务器繁忙，请稍候再试！";
            //    CommonManager.Web.RegJs( this, "alert('抱歉，奖品兑换失败，可能是服务器繁忙，请稍候再试！');location.href=location.href;", true );
            //}
            Dictionary<string, object> dic = new Dictionary<string, object>();
            DbSession.Default.FromProc("Web_pAwardBuy").AddInputParameter("@UserID", DbType.Int32, UiCommon.UserLoginInfo.UserID)
                .AddInputParameter("@Award_ID", DbType.Int32, AwardID)
                .AddInputParameter("@TrueName",DbType.String,trueName)
                .AddInputParameter("@Phone",DbType.String,phone)
                .AddInputParameter("@Address",DbType.String,address)
                .AddInputParameter("@UserRemark",DbType.String,remark)
                .AddInputParameter("@Award_OnLineTime",DbType.Int32,AwardTime)
                .AddReturnValueParameter("@ReturnValue", DbType.Int32)
               .Execute(out dic);
            if (dic.Count <= 0)
                CommonManager.Web.RegJs(this, "alert('抱歉，购买奖品失败，可能是服务器繁忙，请稍后再试！');location.href=location.href;", true);

            if (dic["ReturnValue"].ToString() == "-1")
            {
                CommonManager.Web.RegJs(this, "alert('抱歉，购买奖品失败，您的" + UiCommon.StringConfig.GoldName+ "数不足！');location.href=location.href;", true);
            }
            CommonManager.Web.RegJs(this, "alert('" + ConfigurationManager.AppSettings["DuiJingMgs"] + "');location.href=location.href;", true);
		}
	}
}
