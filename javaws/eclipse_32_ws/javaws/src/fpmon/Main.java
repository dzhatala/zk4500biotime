package fpmon;

import java.io.BufferedReader;
import java.io.Console;
import java.io.IOException;
import java.io.InputStreamReader;
import java.sql.*;  

public class Main {

	/**
	 * @param args
	 */

	static final String q="select IDENTIFIED1N.*, fpinfo.person_id, mdl_user.username,mdl_user.firstname, " +
			"mdl_user.lastname  FROM identified1n left join fpinfo on ( (IDENTIFIED1N.fpid=fpinfo.RIGHT_INDEX) OR (IDENTIFIED1N.fpid=fpinfo.RIGHT_THUMB)OR (IDENTIFIED1N.fpid=fpinfo.RIGHT_INDEX)OR (IDENTIFIED1N.fpid=fpinfo.RIGHT_MIDDLE)OR (IDENTIFIED1N.fpid=fpinfo.RIGHT_RING)OR (IDENTIFIED1N.fpid=fpinfo.RIGHT_PINKY)OR (IDENTIFIED1N.fpid=fpinfo.LEFT_THUMB)OR (IDENTIFIED1N.fpid=fpinfo.LEFT_INDEX)OR (IDENTIFIED1N.fpid=fpinfo.LEFT_MIDDLE)OR " +
			"(IDENTIFIED1N.fpid=fpinfo.LEFT_RING)OR (IDENTIFIED1N.fpid=fpinfo.LEFT_PINKY)OR 0) left  " +
			"join mdl_user on fpinfo.PERSON_ID=mdl_user.id  order by trialdate desc LIMIT 1";

	static int last1Nid=-1;

	public static void logUser(int fid1nID, int fFPID, Date ftrialDate, String ffName, String flName){
		System.out.println("IDENTIFIED1N_ID\tTRIALDATE \tFPID\tSCORE\tPFN\tperson_id\tusername\tfirstname\tlastname"); 	
		System.out.println("   "+fid1nID+"\t\t"+ftrialDate+"\t"+fFPID+"                                               "+
				"\t"+ffName+    "\t\t"  +flName);
		System.out.flush();

	}
	
	
	
	
	public static final long  SLEEP_TIME_MS=1000; //
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("Monitoring Finger Print ..");

		try{  
			Class.forName("com.mysql.jdbc.Driver");  
			String host ="localhost";
			String  user= "joesmart";
			String password="";
			Console cs=System.console();
			System.out.println("Hostname (localhost):");
			String ans = cs.readLine();
			//System.out.println(ans.length());
			if(ans!=null&&ans.length()>0)host=ans;

			System.out.println("Username (joesmart):");
			ans = cs.readLine();
			if(ans!=null&&ans.length()>0)user=ans;

			System.out.println("password (******):");
			char ac[]=cs.readPassword();
			//System.out.println(ac.length);
			if(ac!=null&&ac.length>0)password=new String(ac);

			
			Connection con=DriverManager.getConnection(  
					"jdbc:mysql://"+host+":3306/moodle",user,password);  
			//here sonoo is database name, root is username and password  
			
			password=null;//emptying password
			
			Statement stmt=con.createStatement();  

			while(true){

				ResultSet rs=stmt.executeQuery(q);  

				rs.next();
				//IDENTIFIED1N_ID 	TRIALDATE 	FPID 	SCORE 	PFN 	person_id 	username 	firstname 	lastname 	
				//35 	2018-04-03 05:26:54 	-1 	0 	0 	NULL	NULL	NULL	NULL

				int id1nID=rs.getInt(1);
				int FPID = rs.getInt(3);
				Date trialDate=rs.getDate(2);
				String fName=rs.getString(8); String lName=rs.getString(9);
				//System.out.println(rs.getInt(1)+"  "+rs.getString(2)+"  "+rs.getString(3));  

				if(id1nID>last1Nid){


					if(last1Nid>0){
						//
						//System.out.println();
						if(FPID!=-1){
							logUser(id1nID, FPID, trialDate, fName, lName);
							if(fName!=null&&lName!=null)
								//speakIdentifed1N(FPID,fName, lName);
								speakIdentifed1N_espeak(FPID,fName, lName);
							if(fName==null&&lName==null){

								speakNotInDB(FPID);
							}
						}else 
						{
								speakNotRegistered();
						}


					}else {
						System.out.println("Ignoring first id "+id1nID);
					}
					last1Nid=id1nID;


				}



				Thread.currentThread();
				//System.out.println("Sleeping...");
				//System.out.flush();  
				Thread.sleep(SLEEP_TIME_MS);

			}

			//con.close();  	
		}catch(Exception e){ 
			System.out.println(e);

		}  



	}
	 static void speakNotRegistered() {
		System.out.println("speakNotRegistered ...");
		Thread runner =new Thread(){

			public void run(){
				try {
					Process p=Runtime.getRuntime().exec("/usr/bin/play notregistered.wav");
					p.waitFor();
					//Thread.currentThread();
					//Thread.sleep(1000);
					p=Runtime.getRuntime().exec("/usr/bin/play -v 3.0 tdk_terdaftar.wav");
					p.waitFor();
					p=Runtime.getRuntime().exec("/usr/bin/play -v 3.0 silahkan_ulangi.wav");
					p.waitFor();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();

				}
			}
		};
		runner.start();

		
	}
	 static void speakNotInDB(final int FPID) {
		// TODO Auto-generated method stub
		System.out.println("speakNotInDB ...");
		Thread runner =new Thread(){

			public void run(){
				try {
					
					Process p=Runtime.getRuntime().exec("/usr/bin/play notindb.wav");
					p.waitFor();
					
					/*if(true==true){
						String []args=new String[8];
						
						args[0]="/usr/bin/espeak";args[1]="-p"; args[2]="60";args[3]= "-v";args[4]="mb-id1"; args[5]="-w";
						args[6]="fpid.wav";
						args[7]="'Jari,. Jari,. nomor. "+FPID+"'" ;
								
						p=Runtime.getRuntime().exec(args);
						p.waitFor();
						p=Runtime.getRuntime().exec("/usr/bin/play -v 4.0 fpid.wav");
						p.waitFor();
					}*/
					p=Runtime.getRuntime().exec("/usr/bin/play -v 4.0 tdk_basis_data.wav");
					p.waitFor();
					p=Runtime.getRuntime().exec("/usr/bin/play -v 4.0 silahkan_ulangi.wav");
					p.waitFor();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();

				}
			}
		};
		runner.start();

	}
	private static void speakIdentifed1N(int ffPID, final String ffName, final String flName) {
		// TODO Auto-generated method stub
		System.out.println("speakIdentifed1N ...");
		Thread runner =new Thread(){

			public void run(){
				try {
					/*String cmd="/usr/bin/pico2wave -w test.wav \""+ ffName+ "  " +flName+". Verified.\""; 
				System.out.println(cmd);
				//Runtime.getRuntime().exec(cmd);
					 */


					//String args[]=new String[]{"./picoscripts.sh","-w","test.wav", "\""+ffName ,flName+". Verified"," Verified\""};
					/*if(ffName==null&&flName==null){
					args=new 
				}*/
					String args[]=new String[]{"/usr/bin/pico2wave","-w","test.wav", "Verified."};
					Process p=Runtime.getRuntime().exec(args);
					p.waitFor();
					p=Runtime.getRuntime().exec("/usr/bin/play test.wav");
					p.waitFor();

					if(ffName!=null){
						args=new String[]{"/usr/bin/pico2wave","-w","fN.wav", ffName};
						p=Runtime.getRuntime().exec(args);
						p.waitFor();
						p=Runtime.getRuntime().exec("/usr/bin/play fN.wav");
						p.waitFor();
					}

					if(flName!=null){
						args=new String[]{"/usr/bin/pico2wave","-w","fN.wav", flName};
						p=Runtime.getRuntime().exec(args);
						p.waitFor();
						p=Runtime.getRuntime().exec("/usr/bin/play fN.wav");
						p.waitFor();
					}


					//Runtime.getRuntime().exec("./picoscripts.sh "+ffName+" "+flName);
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();

				}
			}
		};
		runner.start();

	}
	
	
	/** Thread safe **/
	
	public static void speakIdentifed1N_espeak(int ffPID, final String ffName, final String flName) {
		// TODO Auto-generated method stub
		System.out.println("speakIdentifed1N ...");
		Thread runner =new Thread(){

			public void run(){
				try {
					Process p=null;
					String []args=null;
					p=Runtime.getRuntime().exec("/usr/bin/play  verified.wav");
					p.waitFor();
					//Thread.currentThread();
					//Thread.sleep(500);

					if(ffName!=null){
						args=new String[8];
						
						args[0]="/usr/bin/espeak";args[1]="-p"; args[2]="50";args[3]= "-v";args[4]="mb-id1"; args[5]="-w";
						args[6]="espeak.wav";
						args[7]=ffName;
								
						p=Runtime.getRuntime().exec(args);
						p.waitFor();
						p=Runtime.getRuntime().exec("/usr/bin/play -v 4.0 espeak.wav");
						p.waitFor();
					}
					
					if(flName!=null){
							args=new String[8];
							
							args[0]="/usr/bin/espeak";args[1]="-p"; args[2]="50";args[3]= "-v";args[4]="mb-id1"; args[5]="-w";
							args[6]="espeak.wav";
							args[7]=flName;
							p=Runtime.getRuntime().exec(args);
							p.waitFor();
							p=Runtime.getRuntime().exec("/usr/bin/play -v 4.0 espeak.wav");
							p.waitFor();
						}
					
					

				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();

				}
			}
		};
		runner.start();

	}


	
}
