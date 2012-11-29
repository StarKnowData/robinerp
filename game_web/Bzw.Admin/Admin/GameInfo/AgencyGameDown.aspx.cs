using System;
using System.Data;
using System.Web;
using System.IO;
using System.Xml;
using Utility;
using BCST.Common;

public partial class Admin_GameInfo_AgencyGameDown : AdminBasePage
{
	public int RowNum = 1;
	XmlDocument xmlDoc;
	private string xmlPath
	{
		get
		{
			return Server.MapPath(UiCommon.ConstantConfig.XmlFilePath);
		}
	}

	private int Param
	{
		get
		{
			return Common.GetIntOfUrl( "params" );
		}
	}

	private string Actions
	{
		get
		{
			return Common.GetStringOfUrl( "action" );
		}
	}

	protected void Page_Load( object sender, EventArgs e )
	{
		AdminPopedom.IsHoldModel( "06" );
		xmlDoc = new XmlDocument();
		if( !File.Exists( xmlPath ) )
		{
			CreateXMLFile();
		}
		if( !IsPostBack )
		{
			BindData();
			if( Param > 0 && Actions == "edit" )
				getInfo();
			else if( Param > 0 && Actions == "del" )
				DelXml();
		}
	}

	private void DelXml()
	{
		xmlDoc.Load(xmlPath);
		XmlNodeList nodelist = xmlDoc.SelectNodes( "//data[ID='" + Param + "']" );
		XmlNode xn = nodelist.Item( 0 );
		if( xn != null )
		{
			xn.ParentNode.RemoveChild( xn );
			xmlDoc.Save(xmlPath);
			CommonManager.Web.RegJs( this.Page, "alert('删除成功！');location.href='AgencyGameDown.aspx';", true );
		}
		CommonManager.Web.RegJs( this.Page, "alert('删除失败！');", true );
	}

	private void CreateXMLFile()
	{
		XmlDeclaration xmlDec = xmlDoc.CreateXmlDeclaration( "1.0", "utf-8", null );
		xmlDoc.AppendChild( xmlDec );
		XmlElement rootEle = xmlDoc.CreateElement( "root" );
		XmlText rootText = xmlDoc.CreateTextNode( "" );
		rootEle.AppendChild( rootText );
		xmlDoc.AppendChild( rootEle );
		xmlDoc.Save(  xmlPath  );

	}

	private void getInfo()
	{
		xmlDoc.Load( xmlPath );
		XmlNodeList nodelist = xmlDoc.SelectNodes( "root/data[ID='" + Param + "']" );
		XmlNode xn = nodelist.Item( 0 );
		if( xn != null )
		{
			txtTwoDomain.Text = xn["twodomain"].InnerText;
			txtDXUrl.Text = xn["dianxindown"].InnerText;
			txtWTUrl.Text = xn["wangtongdown"].InnerText;
		}
	}

	private void BindData()
	{
		DataSet ds = new DataSet();
		ds.ReadXml( xmlPath );
		if( ds.Tables.Count > 0 )
		{
			rptDataList.DataSource = ds.Tables[0].DefaultView;
			rptDataList.DataBind();
		}
	}
	protected void btnSubmit_Click( object sender, EventArgs e )
	{
		xmlDoc.Load( xmlPath );
		string twoDomain = txtTwoDomain.Text.Trim();
		string dxUrl = txtDXUrl.Text.Trim();
		string wtUrl = txtWTUrl.Text.Trim();
		if( Param > 0 )//修改
		{
			XmlNodeList nodelist = xmlDoc.SelectNodes( "//data[ID='" + Param + "']" );
			XmlNode xn = nodelist.Item( 0 );
			if( xn != null )
			{
				xn["twodomain"].InnerText = twoDomain;
				xn["dianxindown"].InnerText = dxUrl;
				xn["wangtongdown"].InnerText = wtUrl;
				xmlDoc.Save( xmlPath );
				CommonManager.Web.RegJs( this, "alert('保存成功！');location.href=location.href;", true );
			}
		}
		else //添加
		{
			XmlElement newElement = xmlDoc.CreateElement( "data" );
			XmlElement ielement = xmlDoc.CreateElement( "ID" );
			XmlElement telement = xmlDoc.CreateElement( "twodomain" );
			XmlElement delement = xmlDoc.CreateElement( "dianxindown" );
			XmlElement welement = xmlDoc.CreateElement( "wangtongdown" );
			ielement.InnerText = getMaxID();
			telement.InnerText = twoDomain;
			delement.InnerText = dxUrl;
			welement.InnerText = wtUrl;
			newElement.AppendChild( ielement );
			newElement.AppendChild( telement );
			newElement.AppendChild( delement );
			newElement.AppendChild( welement );
			xmlDoc.DocumentElement.AppendChild( newElement );
			xmlDoc.Save( xmlPath );
			CommonManager.Web.RegJs( this, "alert('添加成功！');location.href=location.href;", true );
		}
	}

	private string getMaxID()
	{
		string maxID = "1";
		xmlDoc.Load( xmlPath );
		XmlNode xn = xmlDoc.DocumentElement.LastChild;
		if( xn != null )
		{
			maxID = Convert.ToString( Convert.ToInt32( xn["ID"].InnerText ) + 1 );
		}
		return maxID;
	}

}
