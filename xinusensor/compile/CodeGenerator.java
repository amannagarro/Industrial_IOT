import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.FilenameFilter;
import java.io.IOException;
import java.text.SimpleDateFormat;

import javax.xml.XMLConstants;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.Source;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

public class CodeGenerator {
	
	
	static boolean isDDLModified(File ddl)
	{
		String current = System.getProperty("user.dir");	
		//code to check if DDL is updated or not.
		File ledIO = new File(current+"/../include/actuator.h");
		if (ledIO.exists()) {
			SimpleDateFormat sdf = new SimpleDateFormat("MM/dd/yyyy HH:mm:ss");
			System.out.println("After Format : " + sdf.format(ledIO.lastModified()));
			System.out.println("After Format : " + sdf.format(ddl.lastModified()));
			if(ledIO.lastModified() < ddl.lastModified())
			{
				return true;
			}
		}
		else
		{				
			File digitalIO = new File(current+"/../include/digitalSensor.h");
			if (digitalIO.exists()) {
				if(digitalIO.lastModified() < ddl.lastModified())
				{
					return true;
				}
			}
			else
			{
				File analogIO = new File(current+"/../include/analogSensor.h");
				if(analogIO.lastModified() < ddl.lastModified())
				{
					return true;
				}
			}
		}
		return false;
	}
	
	static void CreateActuatorFile(Document doc)
	{
		String current = System.getProperty("user.dir");		
		NodeList nList = doc.getElementsByTagName("Actuator");
		BufferedWriter bw = null;
		FileWriter fw =null;
		try
		{
			String string;
			File ledIO = new File(current+"/../include/actuator.h");
			if (!ledIO.exists()) {
				ledIO.createNewFile();
			}
			fw = new FileWriter(ledIO);
			bw = new BufferedWriter(fw);
			for(int i =0;i< nList.getLength();i++)
			{
				Element element = (Element) nList.item(i);
				string = "if(strcmp(devptr->dvname,\""+ element.getElementsByTagName("Name").item(0).getTextContent() +"\")==0)\n";				
				string += "actuator_write(1<<"+element.getElementsByTagName("PinNumber").item(0).getTextContent()+",data);\n";
				
				bw.write(string);
			}
		}		
		catch (IOException e) {
			// 	TODO Auto-generated catch block
			e.printStackTrace();
		}
		finally
		{
			try {
				bw.close();
				fw.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}				
		}
	}
	
	static void CreateDigitalSensorFile(Document doc)
	{
		String current = System.getProperty("user.dir");
		BufferedWriter bw1 = null;
		FileWriter fw1 =null;
		try
		{
			//for digital sensor read.
			String string= "";
			File digitalIO = new File(current+"/../include/digitalSensor.h");
			if (!digitalIO.exists()) {
				digitalIO.createNewFile();
			}
			fw1 = new FileWriter(digitalIO);
			bw1 = new BufferedWriter(fw1);
			NodeList nList = doc.getElementsByTagName("DigitalSensor");
			for(int i =0;i< nList.getLength();i++)
			{
				Element element = (Element) nList.item(i);
				string = "if(strcmp(devptr->dvname,\""+ element.getElementsByTagName("Name").item(0).getTextContent() +"\")==0)\n";				
				string += "i = sensor_read(1<<"+element.getElementsByTagName("PinNumber").item(0).getTextContent()+");\n";
								
				bw1.write(string);
			}
		}		
		catch (IOException e) {
			// 	TODO Auto-generated catch block
			e.printStackTrace();
		}
		finally
		{
			try {
				bw1.close();
				fw1.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}				
		}
	}
	
	static void CreateAnalogInitializeSensorFile(Document doc)
	{
		String current = System.getProperty("user.dir");
		BufferedWriter bw2 = null;
		FileWriter fw2 =null;
		try
		{
			String string= "";
			File analogIO = new File(current+"/../include/analogSensorInitialize.h");
			if (!analogIO.exists()) {
				analogIO.createNewFile();
			}
			fw2 = new FileWriter(analogIO);
			bw2 = new BufferedWriter(fw2);
			NodeList nList = doc.getElementsByTagName("AnalogSensor");
			for(int i =0;i< nList.getLength();i++)
			{
				Element element = (Element) nList.item(i);
				String channelNumberString = element.getElementsByTagName("ChannelNumber").item(0).getTextContent();
				int channel = Integer.parseInt(channelNumberString);
				string = "if(strcmp(devptr->dvname,\""+ element.getElementsByTagName("Name").item(0).getTextContent() +"\")==0)\n";				
				string += "(*((unsigned int *)STEP_CONFIG1) |= ("+(channel-1)+"<<19));\n";
								
				bw2.write(string);
			}
		}		
		catch (IOException e) {
			// 	TODO Auto-generated catch block
			e.printStackTrace();
		}
		finally
		{
			try {
				bw2.close();
				fw2.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}				
		}
	}
	
	static void CreateAnalogSensorFile(Document doc)
	{
		String current = System.getProperty("user.dir");
		BufferedWriter bw3 = null;
		FileWriter fw3 =null;
		try
		{
			 //for analog read.
			String string= "";
			File analogIO = new File(current+"/../include/analogSensor.h");
			if (!analogIO.exists()) {
				analogIO.createNewFile();
			}
			fw3 = new FileWriter(analogIO);
			bw3 = new BufferedWriter(fw3);
			NodeList nList = doc.getElementsByTagName("AnalogSensor");
			for(int i =0;i< nList.getLength();i++)
			{
				Element element = (Element) nList.item(i);
				Element element1 = (Element) element.getElementsByTagName("Signal").item(0);
				String variableName = element1.getAttribute("id");
				String formula = element.getElementsByTagName("Expression").item(0).getTextContent();
				String editedFormula = formula.replaceAll(variableName, "milliVolts");
				string = "if(strcmp(devptr->dvname,\""+ element.getElementsByTagName("Name").item(0).getTextContent() +"\")==0)\n";				
				string += "temp_degrees = (uint32)"+editedFormula+";\n";
								
				bw3.write(string);
			}
		}		
		catch (IOException e) {
			// 	TODO Auto-generated catch block
			e.printStackTrace();
		}
		finally
		{
			try {
				bw3.close();
				fw3.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}				
		}
	}

	public static void main(String[] args) {	

		File inputXML = null;
		String current = System.getProperty("user.dir");
		File dir = new File(current);
	    if (dir.isDirectory()) {
	        File[] xmlFiles = dir.listFiles(new FilenameFilter() {
	            @Override
	            public boolean accept(File folder, String name) {
	                return name.toLowerCase().endsWith(".xml");
	            }
	        });
	        inputXML = xmlFiles[0];
	    } 
	    
	    try {
	    	 //check against xsd.		    
		    File xsdFile = new File("DDL.xsd");
		    Source xmlFile = new StreamSource(inputXML);
		    SchemaFactory schemaFactory = SchemaFactory
		        .newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
		    Schema schema = schemaFactory.newSchema(xsdFile);
		    Validator validator = schema.newValidator();
		    validator.validate(xmlFile);
		    DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();                          
		    DocumentBuilder dBuilder = null;

				if(!isDDLModified(inputXML))
				{
					return;
				}
				dBuilder = dbFactory.newDocumentBuilder();
				Document doc = dBuilder.parse(inputXML);
			
				CreateActuatorFile(doc);
				CreateDigitalSensorFile(doc);
				CreateAnalogInitializeSensorFile(doc);
				CreateAnalogSensorFile(doc);
				System.out.println("Parsing done.");
	    }
	    catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
