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
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;

public partial class Public_Getcode : System.Web.UI.Page
{
	protected void Page_Load( object sender, EventArgs e )
	{
		string tmp = RndNum( 4 );
		Session[UiCommon.ValidCode.KeyName] = tmp;
		this.ValidateCode( tmp );

	}
	private void ValidateCode( string VNum )
	{
		Bitmap Img = null;
		Graphics g = null;
		MemoryStream ms = null;

		int gheight = VNum.Length * 10;
		Img = new Bitmap( gheight, 15 );
		g = Graphics.FromImage( Img );
		//背景颜色 
		g.Clear( Color.White );
		//文字字体 
		Font f = new Font( "宋体", 10 );
		//文字颜色 
		SolidBrush s = new SolidBrush( Color.Red );
		g.DrawString( VNum, f, s, 3, 3 );
		ms = new MemoryStream();
		Img.Save( ms, ImageFormat.Jpeg );
		Response.ClearContent();
		Response.ContentType = "images/Jpeg";
		Response.BinaryWrite( ms.ToArray() );
		g.Dispose();
		Img.Dispose();
		Response.End();
	}

	private string RndNum( int VcodeNum )
	{
        String Vchar = "0,1,2,3,4,5,6,7,8,9";
        String[] VcArray = Vchar.Split(',');
        String VNum = "";
        Random random = new Random();
        for (int i = 1; i <= VcodeNum; i++)
        {
            int iNum = 0;
            while ((iNum = Convert.ToInt32(VcArray.Length * random.NextDouble())) == VcArray.Length)
            {
                iNum = Convert.ToInt32(VcArray.Length * random.NextDouble());
            }
            VNum += VcArray[iNum];
            // VNum += VcArray[Convert.ToInt32(VcArray.Length*random.NextDouble())];
        }
        return VNum;
	}
}
