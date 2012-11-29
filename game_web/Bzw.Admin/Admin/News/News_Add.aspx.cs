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
using System.Data.SqlClient;
using Bzw.Data;
using BCST.Common;

public partial class Admin_News_News_Add : AdminBasePage
{
	string NewsID;
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "10" );

		DataTable sd = new DataTable();
		string sql = "select TypeID,TypeName from Web_NewsType order by Typeid desc";
		sd = DbSession.Default.FromSql( sql ).ToDataTable(); 
		if( sd.Rows.Count > 0 )
		{
			this.news_type.DataBind();
			for( int i = 0; i < sd.Rows.Count; i++ )
			{
				this.news_type.Items.Add( new ListItem( sd.Rows[i]["TypeName"].ToString(), sd.Rows[i]["TypeID"].ToString() ) );
			}
		}
		sd.Clear();

		DataTable sd2 = new DataTable();
		string sql2 = "select max(news_id) as newsid  from Web_NewsData";
		sd2 = DbSession.Default.FromSql( sql2 ).ToDataTable(); 
		if( sd2.Rows.Count > 0 )
		{
			NewsID = sd2.Rows[0]["Newsid"].ToString();
			if( NewsID.ToString() == "" )
				NewsID = "0";
		}
		sd2.Clear();
	}


	protected void NewsAd( object sender, EventArgs e )
	{
		string sqltitle = "", sqlnews_type = "", sqlkeywords = "", sqlnews_from = "", sqlauthor = "", sqlissuer = "", sqlcontent = "", sqlpicture = "", sqlthrough = "";
		string sqlrecommendation = "", sqlIstop = "";

		sqltitle = CommonManager.Web.RequestForm( "title", "" ); 
		if( sqltitle.ToString() == "" )
		{
			Alert( "温馨提示：\\n\\n新闻标题不能为空！", null );
			return;
		}
		sqlnews_type = this.news_type.Text;
		sqlkeywords = CommonManager.Web.RequestForm( "keywords", "" ); 
		sqlnews_from = CommonManager.Web.RequestForm( "news_from", "" );
		sqlauthor = CommonManager.Web.RequestForm( "author", "" ); 
		sqlissuer = CommonManager.Web.RequestForm( "issuer", "" ); 
		sqlcontent = content.Value; 
		if( sqlcontent.ToString() == "" ){
			Alert( "温馨提示：\\n\\n新闻内容不能为空！", null );
			return;
		}
		//sqlpicture = CommonManager.Web.RequestForm( "picture", "" ); 
		sqlthrough = CommonManager.Web.RequestForm( "through", "" ); 
		sqlrecommendation = CommonManager.Web.RequestForm( "recommendation", "" ); 
		sqlIstop = CommonManager.Web.RequestForm( "Istop", "" ); 

		if( fuImage.HasFile )
		{
			try
			{
				if( !CommonManager.File.UploadFile( fuImage.PostedFile, 300 * 1024, new string[] { "jpg", "jpeg", "gif" }, "/Upload/News", FileOperator.RenameType.当前时间及随机数字, out sqlpicture ) )
				{
					sqlpicture = "";
				}
			}
			catch( Exception ex )
			{
				Response.Write( "文件上传错误：" + ex.Message + "<a href='javascript:history.back();'>点此返回上一页</a>" );
				return;
			}
		}

		//string sql = @"insert into Web_NewsData (title,titlecolor,News_type,keywords,news_from,author,issuer,Content,News_picture,through) values ()";
		string cmdText = @"INSERT INTO Web_NewsData (
						News_Type,Title,TitleColor,Keywords,News_From,Author,
						Issuer,Content,News_picture,Through,Recommendation,Istop,Issue_Time) 
						VALUES (@News_Type,@Title,@TitleColor,@Keywords,@News_From,@Author,
						@Issuer,@Content,@News_picture,@Through,@Recommendation,@Istop,@Issue_Time)";

		SqlParameter[] param = new SqlParameter[]{
        new SqlParameter("@News_Type", SqlDbType.TinyInt ),
        new SqlParameter("@Title",SqlDbType.NVarChar),
		new SqlParameter("@TitleColor",SqlDbType.NVarChar),
        new SqlParameter("@Keywords",SqlDbType.NVarChar),
        new SqlParameter("@News_From",SqlDbType.NVarChar),
        new SqlParameter("@Author",SqlDbType.NVarChar),
        new SqlParameter("@Issuer",SqlDbType.NVarChar),
        new SqlParameter("@Content",SqlDbType.NText),
        new SqlParameter("@News_picture",SqlDbType.NVarChar),
        new SqlParameter("@Through",SqlDbType.Bit),
		new SqlParameter("@Recommendation",SqlDbType.Bit),
        new SqlParameter("@Istop",SqlDbType.Bit),
        new SqlParameter("@Issue_Time", SqlDbType.SmallDateTime )
    };

		param[0].Value = sqlnews_type;
		param[1].Value = sqltitle;
		param[2].Value = hidTitleColor.Value.Trim();
		param[3].Value = sqlkeywords;
		param[4].Value = sqlnews_from;
		param[5].Value = sqlauthor;
		param[6].Value = sqlissuer;
		param[7].Value = sqlcontent;
		param[8].Value = sqlpicture;
		param[9].Value = sqlthrough == "1" ? true : false;
		param[10].Value = sqlrecommendation == "1" ? true : false;
		param[11].Value = sqlIstop == "1" ? true : false;
		param[12].Value = DateTime.Now;

		//foreach( SqlParameter sp in param )
		//{
		//    Response.Write(sp.Value + "<br />");
		//}
		//Response.End();


		int SqlState = SqlHelper.ExecuteNonQuery( CommandType.Text, cmdText, param );
				
		string adminName = AdminInfo["UserName"].ToString();
		string descript = "添加新闻内容！标题：" + sqltitle;
		string system = Common.GetOS;
		if( SqlState > 0 )
		{
			new BLL.Member().InsertAdminModifyLog( adminName, Common.RequestIP, system, descript, 1 );
			Alert( "温馨提示：\\n\\n新闻添加成功！", "News.aspx");
		}
		else
		{
			new BLL.Member().InsertAdminModifyLog( adminName, Common.RequestIP, system, descript, 0 );
			Alert( "温馨提示：\\n\\n新闻添加失败！", null );
		}
	}
}
