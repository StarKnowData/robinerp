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
using System.Data.SqlClient;
using Utility;
using BCST.Common;
using Bzw.Data;

public partial class Admin_News_NewsEdit : AdminBasePage
{
	string NewsEditId;
	public string title = "", keywords = "", news_from = "", author = "", issuer = "", through = "", recommendation = "", Istop = "";
	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "10" );

		string tmp = CommonManager.Web.Request( "id", "" );
		if( string.IsNullOrEmpty( tmp ) || !CommonManager.String.IsInteger( tmp ) )
		{
			Alert( "请勿非法操作！", null );
			return;
		}
		else
			NewsEditId = tmp; 

		if( !IsPostBack )
		{
			DataTable sd = new DataTable();
			string sql = "select n.*,nc.Typename as typename,nc.typeid as typeid from [Web_NewsData] as n left outer join [Web_NewsType] as nc on n.News_Type=nc.typeid where n.News_id=" + Convert.ToInt32( NewsEditId ) + "";
			sd = DbSession.Default.FromSql( sql ).ToDataTable(); 

			string action = CommonManager.Web.Request( "action", "" );
			if( !string.IsNullOrEmpty( action ) && action == "delimg" )
			{
				//删除图片
				CommonManager.File.DeleteFile( sd.Rows[0]["News_picture"].ToString() );
				DbSession.Default.FromSql( "update Web_NewsData set News_picture='' where News_id=" + tmp ).Execute();
				CommonManager.Web.RegJs( this, @"RefreshMeDelParam('[?&]?action=delimg');", false );
				return;
			}

			if( sd.Rows.Count > 0 && !IsPostBack)
			{
				this.news_type.Items.Add( new ListItem( sd.Rows[0]["Typename"].ToString(), sd.Rows[0]["typeid"].ToString() ) );
				title = sd.Rows[0]["title"].ToString();
				hidTitleColor.Value = sd.Rows[0]["TitleColor"].ToString();
				keywords = sd.Rows[0]["keywords"].ToString();
				news_from = sd.Rows[0]["news_from"].ToString();
				author = sd.Rows[0]["author"].ToString();
				issuer = sd.Rows[0]["issuer"].ToString();
				content.Value = sd.Rows[0]["content"].ToString();
				through = sd.Rows[0]["through"].ToString();
				recommendation = sd.Rows[0]["recommendation"].ToString();
				Istop = sd.Rows[0]["Istop"].ToString();
				//picture.Text = sd.Rows[0]["News_picture"].ToString();

				if( !string.IsNullOrEmpty( sd.Rows[0]["News_picture"].ToString() ) )
				{
					phFileImage.Visible = false;
					phImageUrl.Visible = true;
					txtImageUrl.Text = sd.Rows[0]["News_picture"].ToString();
				}
				else
				{
					phImageUrl.Visible = false;
					phFileImage.Visible = true;
				}

				DataTable sd2 = new DataTable();
				string sql2 = "select TypeID,TypeName from Web_NewsType order by Typeid desc";
				sd2 = DbSession.Default.FromSql( sql2 ).ToDataTable(); //sqlconn.sqlReader( sql2 );
				if( sd2.Rows.Count > 0 )
				{
					this.news_type.DataBind();
					for( int i = 0; i < sd2.Rows.Count; i++ )
					{
						this.news_type.Items.Add( new ListItem( sd2.Rows[i]["TypeName"].ToString(), sd2.Rows[i]["TypeID"].ToString() ) );
					}
				}
				sd2.Clear();
			}
			sd.Clear();
		}
	}

	protected void NewsEd( object sender, EventArgs e )
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
		if( sqlcontent.ToString() == "" )
		{
			Alert( "温馨提示：\\n\\n新闻内容不能为空！", null );
			return;
		}
		
		sqlthrough = CommonManager.Web.RequestForm( "through", "" ); 
		sqlrecommendation = CommonManager.Web.RequestForm( "recommendation", "" );
		sqlIstop = CommonManager.Web.RequestForm( "Istop", "" ); 

		//上传图片
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
		else
		{
			sqlpicture = txtImageUrl.Text.Trim();
		}

		string cmdText = @"UPDATE Web_NewsData SET
					News_Type=@News_Type,Title=@Title,TitleColor=@TitleColor,Keywords=@Keywords,News_From=@News_From,
					Author=@Author,Issuer=@Issuer,Content=@Content,News_picture=@News_picture,
					Through=@Through,Recommendation=@Recommendation,Istop=@Istop,Issue_Time=@Issue_Time WHERE News_ID=@News_ID";

		SqlParameter[] param = new SqlParameter[]{
        new SqlParameter("@News_ID",SqlDbType.Int),
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

		param[0].Value = NewsEditId;
		param[1].Value = sqlnews_type;
		param[2].Value = sqltitle;
		param[3].Value = hidTitleColor.Value.Trim();
		param[4].Value = sqlkeywords;
		param[5].Value = sqlnews_from;
		param[6].Value = sqlauthor;
		param[7].Value = sqlissuer;
		param[8].Value = sqlcontent;
		param[9].Value = sqlpicture;
		param[10].Value = sqlthrough == "1" ? true : false;
		param[11].Value = sqlrecommendation == "1" ? true : false;
		param[12].Value = sqlIstop == "1" ? true : false;
		param[13].Value = DateTime.Now;

		int SqlState = SqlHelper.ExecuteNonQuery( CommandType.Text, cmdText, param );

		
		string adminName = AdminInfo["UserName"].ToString();
		string descript = "修改新闻内容！标题：" + sqltitle;
		string system = Common.GetOS;
		if( SqlState > 0 )
		{
			new BLL.Member().InsertAdminModifyLog( adminName, Common.RequestIP, system, descript, 1 );
			Alert( "温馨提示：\\n\\n新闻修改成功！", "News.aspx" );
		}
		else
		{
			new BLL.Member().InsertAdminModifyLog( adminName, Common.RequestIP, system, descript, 0 );
			Alert( "温馨提示：\\n\\n新闻修改失败！", null );
		}
	}
}
