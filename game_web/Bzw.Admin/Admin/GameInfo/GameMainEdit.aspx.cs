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

public partial class Admin_GameInfo_GameMainEdit : AdminBasePage
{
	string gameids;

	public string Game_Name = "", Down_address = "", FileSize = "", Provice = "", area = "", Image_URL = "", Game_Order = "", Game_Process = "", MatchTable = "", Through = "";
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "06" );

		string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			CommonManager.Web.RegJs( this, "alert('请勿非法操作！');", false );
			return;
		}
		else
			gameids = tmp; //Limit.editCharacter(Limit.getFormValue("id"));

		DataTable sd1 = new DataTable();
        string sql1 = "select n.*,nc.KindName as TypeName,nc.KindID as Typeid from [web_GameInfo] as n left outer join [TGameKindInfo] as nc on n.Game_typeid=nc.kindid where n.Game_id=" + gameids + "";
		sd1 = DbSession.Default.FromSql( sql1 ).ToDataTable(); //sqlconn.sqlReader(sql1);
		if( sd1.Rows.Count <= 0 )
			return;

		string action = CommonManager.Web.Request("action","");
		if( !string.IsNullOrEmpty( action ) && action == "delimg" )
		{
			//删除图片
			CommonManager.File.DeleteFile( sd1.Rows[0]["Image_Url"].ToString() );
			DbSession.Default.FromSql( "update web_GameInfo set Image_Url='' where Game_id=" + tmp ).Execute();
			CommonManager.Web.RegJs( this, @"RefreshMeDelParam('[?&]?action=delimg');", false );
			return;
		}

		//Limit.ToString().ToLower
		if( sd1.Rows.Count > 0 && !IsPostBack )
		{
			this.Game_TypeID.Items.Add( new ListItem( sd1.Rows[0]["TypeName"].ToString(), sd1.Rows[0]["Typeid"].ToString() ) );
			this.Game_Name = sd1.Rows[0]["Game_Name"].ToString();
			this.Down_address = sd1.Rows[0]["Down_address"].ToString();
			this.FileSize = sd1.Rows[0]["FileSize"].ToString();
			this.Provice = sd1.Rows[0]["Provice"].ToString();
			this.area = sd1.Rows[0]["area"].ToString();
			this.Image_URL = sd1.Rows[0]["Image_Url"].ToString();
			this.Game_Order = sd1.Rows[0]["Game_Order"].ToString();
			this.Game_Process = sd1.Rows[0]["Game_Process"].ToString();
			this.MatchTable = sd1.Rows[0]["MatchTable"].ToString();
			this.Game_Info.Value = sd1.Rows[0]["Game_Info"].ToString();
			this.Game_Rule.Value = sd1.Rows[0]["Game_Rule"].ToString();
			this.Through = sd1.Rows[0]["Through"].ToString();
            this.cbIsHot.Checked = (bool)sd1.Rows[0]["IsHot"];
			if( string.IsNullOrEmpty( Image_URL ) )
			{
				phFileUpload.Visible = true;
				phImageUrl.Visible = false;
			}
			else
			{
				phImageUrl.Visible = true;
				phFileUpload.Visible = false;
				txtImageUrl.Text = Image_URL;
			}

			DataTable sd = new DataTable();
            string sql = "select KindID,KindName from TGameKindInfo where enable=1 order by KindID desc";
			sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader(sql);
			if( sd.Rows.Count > 0 )
			{
				this.Game_TypeID.DataBind();
				for( int i = 0; i < sd.Rows.Count; i++ )
				{
                    this.Game_TypeID.Items.Add(new ListItem(sd.Rows[i]["KindName"].ToString(), sd.Rows[i]["KindID"].ToString()));
				}
			}
			sd.Clear();
		}
	}


	protected void GameMainEdit( object sender, EventArgs e )
	{
		string sqlDown_address, sqlFileSize, sqlProvice, sqlarea, sqlGame_TypeID, sqlImage_URL;
		string sqlGame_Order, sqlGame_Process, sqlMatchTable, sqlGame_Info, sqlGame_Rule, sqlThrough;
		sqlDown_address = CommonManager.Web.RequestForm( "Down_address", "" );//Limit.editCharacter(Limit.getFormValue("Down_address"));
		sqlFileSize = CommonManager.Web.RequestForm( "FileSize", "" );//Limit.editCharacter(Limit.getFormValue("FileSize"));
        int sqlIsHot = 0;
		if (!CommonManager.String.IsInteger(sqlFileSize))
		{
			CommonManager.Web.RegJs(this, "alert('[文件大小]必须为数字！');location.href=location.href;", false);
			return;
		}
		sqlProvice = CommonManager.Web.RequestForm( "Provice", "" );//Limit.editCharacter(Limit.getFormValue("Provice"));
		sqlarea = CommonManager.Web.RequestForm( "area", "" );//Limit.editCharacter(Limit.getFormValue("area"));
		sqlGame_TypeID = CommonManager.Web.RequestForm( "Game_TypeID", "" );//Limit.editCharacter(Limit.getFormValue("Game_TypeID"));
		//sqlImage_URL = CommonManager.Web.RequestForm( "Image_URL", "" );//Limit.editCharacter(Limit.getFormValue("Image_URL"));
		sqlGame_Order = CommonManager.Web.RequestForm( "Game_Order", "" );//Limit.editCharacter(Limit.getFormValue("Game_Order"));
		if (!CommonManager.String.IsInteger(sqlGame_Order))
		{
			CommonManager.Web.RegJs(this, "alert('[游戏排列号]必须为数字！');location.href=location.href;", false);
			return;
		}
		sqlGame_Process = CommonManager.Web.RequestForm( "Game_Process", "" );//Limit.editCharacter(Limit.getFormValue("Game_Process"));
		sqlMatchTable = CommonManager.Web.RequestForm( "MatchTable", "" );//Limit.editCharacter(Limit.getFormValue("MatchTable"));
		sqlGame_Info = Game_Info.Value; //CommonManager.Web.RequestForm( "Game_Info", "" );//Limit.getFormValue("Game_Info");
		sqlGame_Rule = Game_Rule.Value;//CommonManager.Web.RequestForm( "Game_Rule", "" );//Limit.getFormValue("Game_Rule");
		sqlThrough = CommonManager.Web.RequestForm( "Through", "" );//Limit.editCharacter(Limit.getFormValue("Through"));
        sqlIsHot = Convert.ToInt32(cbIsHot.Checked);
		//上传图片
		if( fuImageUrl.HasFile )
		{
			try
			{
				if( !CommonManager.File.UploadFile( fuImageUrl.PostedFile, 300 * 1024, new string[] { "jpg", "jpeg", "gif" }, "/Upload/GameMain", FileOperator.RenameType.当前时间及随机数字, out sqlImage_URL ) )
				{
					sqlImage_URL = "";
				}
			}
			catch( Exception ex )
			{
				//Response.Write( "文件上传错误：" + ex.Message + "<a href='javascript:history.back();'>点此返回上一页</a>" );
				CommonManager.Web.RegJs(this, "alert('文件上传错误：" + ex.Message + "');location.href=location.href;", false);
				return;
			}
		}
		else
		{
			sqlImage_URL = txtImageUrl.Text.Trim();
		}

		string sql = @"
					update Web_GameInfo set 
							Down_address=@Down_address,
							FileSize=@FileSize,
							Provice=@Provice,
							area=@area,
							Game_TypeID=@Game_TypeID,
							Image_URL=@Image_URL,
							Game_Order=@Game_Order,
							Game_Process=@Game_Process,
							MatchTable=@MatchTable,
							Game_Info=@Game_Info,
							Game_Rule=@Game_Rule,
							Through=@Through,
							update_time=getdate(),
							IsHot=@IsHot where Game_id=@GameID";

		DbSession.Default.FromSql( sql )
				.AddInputParameter( "@Down_address", DbType.String, sqlDown_address )
				.AddInputParameter( "@FileSize", DbType.String, sqlFileSize )
				.AddInputParameter( "@Provice", DbType.String, sqlProvice )
				.AddInputParameter( "@area", DbType.String, sqlarea )
				.AddInputParameter( "@Game_TypeID", DbType.String, sqlGame_TypeID )
				.AddInputParameter( "@Image_URL", DbType.String, sqlImage_URL )
				.AddInputParameter( "@Game_Order", DbType.String, sqlGame_Order )
				.AddInputParameter( "@Game_Process", DbType.String, sqlGame_Process )
				.AddInputParameter( "@MatchTable", DbType.String, sqlMatchTable )
				.AddInputParameter( "@Game_Info", DbType.String, sqlGame_Info )
				.AddInputParameter( "@Game_Rule", DbType.String, sqlGame_Rule )
				.AddInputParameter( "@Through", DbType.String, sqlThrough )
				.AddInputParameter( "@GameID", DbType.Int32, gameids )
                .AddInputParameter("@IsHot", DbType.Int32, sqlIsHot)
				.Execute();

		CommonManager.Web.RegJs( this, "alert('操作成功！');location.href='GameMain.aspx';", false );


		/*
		sqlGame_Name = Limit.editCharacter( Limit.getFormValue( "Game_Name" ) );
		sqlDown_address = Limit.editCharacter( Limit.getFormValue( "Down_address" ) );
		sqlFileSize = Limit.editCharacter( Limit.getFormValue( "FileSize" ) );
		sqlProvice = Limit.editCharacter( Limit.getFormValue( "Provice" ) );
		sqlarea = Limit.editCharacter( Limit.getFormValue( "area" ) );
		sqlGame_TypeID = Limit.editCharacter( Limit.getFormValue( "Game_TypeID" ) );
		sqlImage_URL = Limit.editCharacter( Limit.getFormValue( "Image_URL" ) );
		sqlGame_Order = Limit.editCharacter( Limit.getFormValue( "Game_Order" ) );
		sqlGame_Process = Limit.editCharacter( Limit.getFormValue( "Game_Process" ) );
		sqlMatchTable = Limit.editCharacter( Limit.getFormValue( "MatchTable" ) );
		sqlGame_Info = Limit.getFormValue( "Game_Info" );
		sqlGame_Rule = Limit.getFormValue( "Game_Rule" );
		sqlThrough = Limit.editCharacter( Limit.getFormValue( "Through" ) );
		//Response.Write(sqlGame_Rule + "<br>");
		//Response.Write(sqlGame_Info);
		//Response.End();
		Hashtable ind = new Hashtable();
		//ind.Add("game_id", gameids);
		ind.Add( "Game_Name", sqlGame_Name );
		ind.Add( "Down_address", sqlDown_address );
		ind.Add( "FileSize", sqlFileSize );
		ind.Add( "Provice", sqlProvice );
		ind.Add( "area", sqlarea );
		ind.Add( "Game_TypeID", sqlGame_TypeID );
		ind.Add( "Image_URL", sqlImage_URL );
		ind.Add( "Game_Order", sqlGame_Order );
		ind.Add( "Game_Process", sqlGame_Process );
		ind.Add( "MatchTable", sqlMatchTable );
		ind.Add( "Game_Info", sqlGame_Info.ToString() );
		ind.Add( "Game_Rule", sqlGame_Rule.ToString() );

		ind.Add( "Through", sqlThrough );
		ind.Add( "update_time", DateTime.Now );

		int SqlState = sqlconn.sqlExecute( ind, "[web_GameInfo]", "Game_id=" + gameids + "", 2 );
		ind.Clear();

		if( SqlState > 0 )
		{
			//string sql = "select top 1 NameID from TGameNameInfo where ComName like '%" + sqlGame_Name + "%'";
			//object objGameId = sqlconn.sqlExecScalar(sql);
			//if (objGameId != null)
			//{
			//    BuildHtml(objGameId.ToString());
			//}

			Limit.outMsgBox( "温馨提示：\\n\\n游戏页面修改成功！", "GameMain.aspx", true );
		}
		else
			Limit.outMsgBox( "温馨提示：\\n\\n游戏页面修改失败！", true );*/
	}

	public void BuildHtml( string nameId )
	{
		//WebRequest
		// Create a request for the URL. 		
		System.Net.WebRequest request = System.Net.WebRequest.Create( "http://" + Request.ServerVariables["Http_Host"] + "/app/ShowGameHtml.aspx?id=" + nameId );
		request.Timeout = 10000; //毫秒
		// If required by the server, set the credentials.
		request.Credentials = System.Net.CredentialCache.DefaultCredentials;
		// Get the response.
		System.Net.HttpWebResponse response = (System.Net.HttpWebResponse)request.GetResponse();

		//
		string charset = response.CharacterSet;

		// Get the stream containing content returned by the server.
		System.IO.Stream dataStream = response.GetResponseStream();

		// Open the stream using a StreamReader for easy access.
		System.Text.Encoding encode = System.Text.Encoding.GetEncoding( charset );
		System.IO.StreamReader reader = new System.IO.StreamReader( dataStream, encode );

		//获取文件路径
		string FILE_NAME = Server.MapPath( "/Html/GameInfo/" + nameId + ".html" );
		if( System.IO.File.Exists( FILE_NAME ) )
		{
			System.IO.File.Delete( FILE_NAME );
		}

		//Read the content，把文件保存到网站指定的目录下
		System.IO.File.WriteAllText( FILE_NAME, reader.ReadToEnd(), encode );

		// Cleanup the streams and the response.
		reader.Close();
		dataStream.Close();
		response.Close();
	}
}
