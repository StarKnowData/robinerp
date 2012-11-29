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


public partial class Admin_GameInfo_GameMain_Add : AdminBasePage
{
    string gameids;
    protected void Page_Load(object sender, EventArgs e)
    {
        AdminPopedom.IsHoldModel("06");

        DataTable sd = new DataTable();
        string sql = "select * from TGameKindInfo where Enable=1 order by kindid desc";
		sd = DbSession.Default.FromSql( sql ).ToDataTable(); //sqlconn.sqlReader(sql);
        if (sd.Rows.Count > 0)
        {
            this.Game_TypeID.DataBind();
            for (int i = 0; i < sd.Rows.Count; i++)
            {
                this.Game_TypeID.Items.Add(new ListItem(sd.Rows[i]["KindName"].ToString(), sd.Rows[i]["KindID"].ToString()));
            }
        }
        sd.Clear();
         sql = "select NameID,ComName from TGameNameInfo where NameId not in(select Game_id from web_gameinfo ) and  Enable=1 order by IDSort desc";
         sd = DbSession.Default.FromSql(sql).ToDataTable();
         if (sd.Rows.Count > 0)
         { 
         
             for(int i=0;i<sd.Rows.Count;i++)
             {
                 this.Game_Name.Items.Add(new ListItem(sd.Rows[i]["comname"].ToString(), sd.Rows[i]["nameid"].ToString()));
             
             }
         
         
         }
        


        sd.Clear();

        DataTable sd2 = new DataTable();
        string sql2 = "select max(Game_ID) as gameid from web_GameInfo";
		sd2 = DbSession.Default.FromSql( sql2 ).ToDataTable();//sqlconn.sqlReader(sql2);
        if (sd2.Rows.Count > 0)
        {
            this.gameids = sd2.Rows[0]["gameid"].ToString();
            if (gameids.ToString() == "")
                gameids = "0";
        }
        sd2.Clear();

        
    }

    protected void GameMainAdd(object sender, EventArgs e)
    {
		string sqlGame_Name = "", sqlDown_address = "", sqlFileSize = "", sqlProvice = "", sqlarea = "", sqlGame_TypeID = "", sqlImage_URL = "";
		string sqlGame_Order = "", sqlGame_Process = "", sqlMatchTable = "", sqlGame_Info = "", sqlGame_Rule = "", sqlThrough = "",sqlGame_Id="";
        int sqlIsHot = 0;
		sqlGame_Id = CommonManager.Web.RequestForm( "Game_Name", "" );
        sqlGame_Name = this.Game_Name.SelectedItem.Text;
		sqlDown_address = CommonManager.Web.RequestForm( "Down_address", "" );
		
		sqlFileSize = CommonManager.Web.RequestForm( "FileSize", "" );
		if (!CommonManager.String.IsInteger(sqlFileSize))
		{
			CommonManager.Web.RegJs(this, "alert('[文件大小]必须为数字！');location.href=location.href;", false);
			return;
		}
		sqlProvice = CommonManager.Web.RequestForm( "Provice", "" );
		sqlarea = CommonManager.Web.RequestForm( "area", "" );
		sqlGame_TypeID = CommonManager.Web.RequestForm( "Game_TypeID", "" );
		//sqlImage_URL = CommonManager.Web.RequestForm( "Image_URL", "" );
		sqlGame_Order = CommonManager.Web.RequestForm( "Game_Order", "" );
		if (!CommonManager.String.IsInteger(sqlGame_Order))
		{
			CommonManager.Web.RegJs(this, "alert('[游戏排列号]必须为数字！');location.href=location.href;", false);
			return;
		}
		sqlGame_Process = CommonManager.Web.RequestForm( "Game_Process", "" );
		sqlMatchTable = CommonManager.Web.RequestForm( "MatchTable", "" );
		sqlGame_Info = Game_Info.Value;
		sqlGame_Rule = Game_Rule.Value;
		sqlThrough = CommonManager.Web.RequestForm( "Through", "" );
        sqlIsHot = Convert.ToInt32(cbIsHot.Checked);
		//上传图片
		if( fuImageUrl.HasFile )
		{
			try
			{
				if( !CommonManager.File.UploadFile( fuImageUrl.PostedFile, 300 * 1024, new string[] { "jpg", "jpeg", "gif" }, "/Upload/GameMain" , FileOperator.RenameType.当前时间及随机数字, out sqlImage_URL ) )
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

		string sql = @"
					insert Web_GameInfo (Game_ID,Game_Name,Down_address,FileSize,Provice,area,Game_TypeID,Image_URL,
							Game_Order,Game_Process,MatchTable,Game_Info,Game_Rule,Through,update_time,IsHot)
					values(@Game_ID,@Game_Name,@Down_address,@FileSize,@Provice,@area,@Game_TypeID,@Image_URL,
						@Game_Order,@Game_Process,@MatchTable,@Game_Info,@Game_Rule,@Through,getdate(),@IsHot)
					";
		DbSession.Default.FromSql( sql )
				.AddInputParameter( "@Game_Name", DbType.String, sqlGame_Name )
				.AddInputParameter( "@Down_address", DbType.String, sqlDown_address )
				.AddInputParameter( "@FileSize", DbType.String, sqlFileSize )
				.AddInputParameter( "@Provice", DbType.String, sqlProvice )
				.AddInputParameter( "@area", DbType.String, sqlarea )
				.AddInputParameter( "@Game_TypeID", DbType.String, sqlGame_TypeID )
				.AddInputParameter( "@Image_URL", DbType.String, string.IsNullOrEmpty( sqlImage_URL ) ? "" : sqlImage_URL )
				.AddInputParameter( "@Game_Order", DbType.String, sqlGame_Order )
				.AddInputParameter( "@Game_Process", DbType.String, sqlGame_Process )
				.AddInputParameter( "@MatchTable", DbType.String, sqlMatchTable )
				.AddInputParameter( "@Game_Info", DbType.String, sqlGame_Info )
				.AddInputParameter( "@Game_Rule", DbType.String, sqlGame_Rule )
				.AddInputParameter( "@Through", DbType.String, sqlThrough )
                .AddInputParameter("@IsHot",DbType.Int32,sqlIsHot)
                .AddInputParameter("@Game_ID",DbType.Int32,sqlGame_Id)
				.Execute();

		CommonManager.Web.RegJs( this, "alert('操作成功！');location.href='GameMain.aspx';", false );

		/*
        Hashtable ind = new Hashtable();
        //ind.Add("game_id", Convert.ToInt32(gameids) + Convert.ToInt32(1));
        ind.Add("Game_Name", sqlGame_Name);
        ind.Add("Down_address", sqlDown_address);
        ind.Add("FileSize", sqlFileSize);
        ind.Add("Provice", sqlProvice);
        ind.Add("area", sqlarea);
        ind.Add("Game_TypeID", sqlGame_TypeID);
        ind.Add("Image_URL", sqlImage_URL);
        ind.Add("Game_Order", sqlGame_Order);
        ind.Add("Game_Process", sqlGame_Process);
        ind.Add("MatchTable", sqlMatchTable);
        ind.Add("Game_Info", sqlGame_Info);
        ind.Add("Game_Rule", sqlGame_Rule);
        ind.Add("Through", sqlThrough);
        ind.Add("update_time", DateTime.Now);

        int SqlState = sqlconn.sqlExecute(ind, "[web_GameInfo]", 1);
        ind.Clear();

        if (SqlState > 0)
        {
            //string sql = "select top 1 NameID from TGameNameInfo where ComName like '%" + sqlGame_Name + "%'";
            //object objGameId = sqlconn.sqlExecScalar(sql);
            //if (objGameId != null)
            //{
            //    BuildHtml(objGameId.ToString());
            //}

            Limit.outMsgBox("温馨提示：\\n\\n游戏页面添加成功！", "GameMain.aspx", true);
        }
        else
            Limit.outMsgBox("温馨提示：\\n\\n游戏页面添加失败！", true);*/
    }

    public void BuildHtml(string nameId)
    {
        //WebRequest
        // Create a request for the URL. 		
        System.Net.WebRequest request = System.Net.WebRequest.Create("http://" + Request.ServerVariables["Http_Host"] + "/app/ShowGameHtml.aspx?id=" + nameId);
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
        System.Text.Encoding encode = System.Text.Encoding.GetEncoding(charset);
        System.IO.StreamReader reader = new System.IO.StreamReader(dataStream, encode);

        //获取文件路径
        string FILE_NAME = Server.MapPath("/Html/GameInfo/" + nameId + ".html");
        if (System.IO.File.Exists(FILE_NAME))
        {
            System.IO.File.Delete(FILE_NAME);
        }

        //Read the content，把文件保存到网站指定的目录下
        System.IO.File.WriteAllText(FILE_NAME, reader.ReadToEnd(), encode);

        // Cleanup the streams and the response.
        reader.Close();
        dataStream.Close();
        response.Close();
    }
}
