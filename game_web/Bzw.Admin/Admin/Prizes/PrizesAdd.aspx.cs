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
using BCST.Common;
using Bzw.Data;

public partial class Admin_Prizes_PrizesAdd : AdminBasePage
{
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "11" );
	}

	protected void Prizes_Add( object sender, EventArgs e )
	{
		string sqlAward_Name = "", sqlleitype = "", sqlAward_MoneyCost = "", sqlAward_OnLineTime = "", sqlAward_Num = "", sqlpicture = "/UpLoad/Prizes/NoPic.Jpg", sqlAward_Info = "", sqlAward_hot = "";

		sqlAward_Name = CommonManager.Web.RequestForm( "Award_Name", "" );
		if( sqlAward_Name.ToString() == "" )
		{
			Alert( "温馨提示：\\n\\n奖品名称不能为空！", null );
			return;
		}
		sqlleitype = CommonManager.Web.RequestForm( "leitype", "" );
        Int64 moneyc;
		sqlAward_MoneyCost = CommonManager.Web.RequestForm( "Award_MoneyCost", "" );
		if (!Int64.TryParse(sqlAward_MoneyCost,out moneyc) || Convert.ToInt64(sqlAward_MoneyCost) < 0)
		{
			//sqlAward_MoneyCost = "1";
			CommonManager.Web.RegJs(this, "alert('[奖品所需金币数]必须为不小于0的数字！');location.href=location.href;", false);
			return;
		}
		sqlAward_OnLineTime = CommonManager.Web.RequestForm( "Award_OnLineTime", "" );
		if (!CommonManager.String.IsInteger(sqlAward_OnLineTime) || Convert.ToInt32(sqlAward_OnLineTime) < 0)
		{
			//sqlAward_MoneyCost = "1";
			CommonManager.Web.RegJs(this, "alert('[奖品所需游戏时长数]必须为不小于0的数字！');location.href=location.href;", false);
			return;
		}
		sqlAward_Num = CommonManager.Web.RequestForm( "Award_Num", "" );//Limit.editCharacter( Limit.getFormValue( "Award_Num" ) );
		if (!CommonManager.String.IsInteger(sqlAward_Num) || Convert.ToInt32(sqlAward_Num) < 0)
		{
			//sqlAward_MoneyCost = "1";
			CommonManager.Web.RegJs(this, "alert('[奖品数量]必须为不小于0的数字！');location.href=location.href;", false);
			return;
		}
		//sqlpicture = CommonManager.Web.RequestForm( "picture", "" );//Limit.editCharacter( Limit.getFormValue( "picture" ) );
		sqlAward_Info = CommonManager.Web.RequestForm( "Award_Info", "" );//Limit.editCharacter( Limit.getFormValue( "Award_Info" ) );
		sqlAward_hot = CommonManager.Web.RequestForm( "Award_hot", "" );//Limit.editCharacter( Limit.getFormValue( "Award_hot" ) );

		if( fuImageUrl.HasFile )
		{
			try
			{
				if( !CommonManager.File.UploadFile( fuImageUrl.PostedFile, 300 * 1024, new string[] { "jpg", "jpeg", "gif" }, "/Upload/Prizes", FileOperator.RenameType.当前时间及随机数字, out sqlpicture ) )
				{
					sqlpicture = "/UpLoad/Prizes/NoPic.Jpg";
				}
			}
			catch( Exception ex )
			{
				//Response.Write( "文件上传错误：" + ex.Message + "<a href='javascript:history.back();'>点此返回上一页</a>" );
				CommonManager.Web.RegJs(this, "alert('文件上传错误：" + ex.Message + "');location.href=location.href;", false);
				return;
			}
		}

		string sql = @"INSERT INTO [Web_Award](
	[Award_Name],[Award_Info],[Award_Pic],[Award_Num],[Award_MoneyCost],[Award_Type],[Award_AddDate],[Award_Hot],[Award_OnLineTime]
	)VALUES(
	@Award_Name,@Award_Info,@Award_Pic,@Award_Num,@Award_MoneyCost,@Award_Type,getdate(),
@Award_Hot,@Award_OnLineTime
	)";
		int SqlState = DbSession.Default.FromSql( sql )
			.AddInputParameter( "@Award_Name", DbType.String, sqlAward_Name )
			.AddInputParameter( "@Award_Info", DbType.String, sqlAward_Info )
			.AddInputParameter( "@Award_Pic", DbType.String, sqlpicture )
			.AddInputParameter( "@Award_Num", DbType.String, sqlAward_Num )
			.AddInputParameter( "@Award_MoneyCost", DbType.String, sqlAward_MoneyCost )
			.AddInputParameter( "@Award_Type", DbType.String, sqlleitype )
			.AddInputParameter( "@Award_Hot", DbType.String, sqlAward_hot )
			.AddInputParameter( "@Award_OnLineTime", DbType.String, sqlAward_OnLineTime )
			.Execute();

		string adminName = AdminInfo["UserName"].ToString();
		string descript = "添加奖品资料！奖品名称：" + sqlAward_Name;
		string system = Common.GetOS;
		if( SqlState >= 0 )
		{
			new BLL.Member().InsertAdminModifyLog(adminName, Common.RequestIP, system, descript, 1 );
			Alert( "温馨提示：\\n\\n奖品资料添加成功！", "Prizes.aspx" );
		}
		else
		{
			new BLL.Member().InsertAdminModifyLog( adminName, Common.RequestIP, system, descript, 0 );
			Alert( "温馨提示：\\n\\n奖品资料添加失败！", null );
		}	
	}
}
