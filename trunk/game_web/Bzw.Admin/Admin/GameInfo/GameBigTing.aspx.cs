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
using BCST.Common;

public partial class Admin_GameInfo_GameBigTing : AdminBasePage
{
	string Mid;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "06" );

		DataTable sd = new DataTable();
		string sql = "select top 1 * from web_Gamemain ";
		sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlcon.sqlReader(sql);
		if( sd.Rows.Count > 0 )
		{
			Mid = sd.Rows[0]["Main_id"].ToString();

			GameBig.DataSource = sd;
			GameBig.DataBind();
		}
		sd.Clear();
	}

	protected void GameBigEdit( object sender, EventArgs e )
	{
		string sqlMain_copy, sqlMain_use, sqlDown_address, sqlDown_num, sqlFileSize, sqlImage_URL, sqlMain_info, sqlDown_saddress;
		sqlMain_copy = CommonManager.Web.RequestForm( "Main_copy", "" ); //Limit.editCharacter(Limit.getFormValue("Main_copy"));
		sqlMain_use = CommonManager.Web.RequestForm( "Main_use", "" ); //Limit.editCharacter(Limit.getFormValue("Main_use"));
		sqlDown_num = CommonManager.Web.RequestForm( "Down_num", "" ); //Limit.editCharacter(Limit.getFormValue("Down_num"));
		sqlDown_address = CommonManager.Web.RequestForm( "Down_address", "" ); //Limit.editCharacter(Limit.getFormValue("Down_address"));
		sqlDown_saddress = CommonManager.Web.RequestForm( "Down_saddress", "" ); //Limit.editCharacter(Limit.getFormValue("Down_saddress"));
		sqlFileSize = CommonManager.Web.RequestForm( "FileSize", "" ); //Limit.editCharacter(Limit.getFormValue("FileSize"));
		if (!CommonManager.String.IsInteger(sqlFileSize))
		{
			CommonManager.Web.RegJs(this, "alert('[文件大小]必须为数字！');location.href=location.href;", false);
			return;
		}
		sqlImage_URL = CommonManager.Web.RequestForm( "Image_URL", "" ); //Limit.editCharacter(Limit.getFormValue("Image_URL"));
		sqlMain_info = CommonManager.Web.RequestForm( "Main_info", "" ); //Limit.getFormValue("Main_info").Replace("'","''");
		if( sqlMain_info.Trim().Length > 500 )
		{
			Alert( "温馨提示：\\n\\n游戏大厅介绍的字符个数不能超过500！", null);
			return;
		}

		string sql = @"update web_Gamemain set 
						main_copy=@main_copy,
						main_use=@main_use,
						down_address=@down_address,
						down_saddress=@down_saddress,
						down_num=@down_num,
						filesize=@filesize,
						image_url=@image_url,
						Main_info=@Main_info,
						Update_Time=getdate()
						where Main_id=@Main_id
						";

		DbSession.Default.FromSql( sql )
			.AddInputParameter( "@main_copy", DbType.String, sqlMain_copy )
			.AddInputParameter( "@main_use", DbType.String, sqlMain_use )
			.AddInputParameter( "@down_address", DbType.String, sqlDown_address )
			.AddInputParameter( "@down_saddress", DbType.String, sqlDown_saddress )
			.AddInputParameter( "@down_num", DbType.String, sqlDown_num )
			.AddInputParameter( "@filesize", DbType.String, sqlFileSize )
			.AddInputParameter( "@image_url", DbType.String, sqlImage_URL )
			.AddInputParameter( "@Main_info", DbType.String, sqlMain_info )
			.AddInputParameter( "@Main_id", DbType.String, Mid )
			.Execute();

		CommonManager.Web.RegJs( this, "alert('游戏大厅信息更新成功！');location.href='GameBigTing.aspx';", false );

		/*
				Hashtable ind = new Hashtable();
				//ind.Add("Main_id", Mid);
				ind.Add("main_copy", sqlMain_copy);
				ind.Add("main_use", sqlMain_use);
				ind.Add("down_address", sqlDown_address);
				ind.Add("down_saddress", sqlDown_saddress); 
				ind.Add("down_num", sqlDown_num);
				ind.Add("filesize", sqlFileSize);
				ind.Add("image_url", sqlImage_URL);
				ind.Add("Main_info", sqlMain_info);
				ind.Add("Update_Time", DateTime.Now);
				int SqlState = sqlcon.sqlExecute(ind, "[web_Gamemain]", "Main_id='" + Mid + "'", 2);
				if (SqlState > 0)
					Limit.outMsgBox("温馨提示：\\n\\n游戏大厅信息更新成功！", "GameBigTing.aspx", true);
				else
					Limit.outMsgBox("温馨提示：\\n\\n游戏大厅信息更新失败！", true);*/
	}
}
