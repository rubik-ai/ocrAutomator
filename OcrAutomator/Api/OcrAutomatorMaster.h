#pragma once
#include <memory>
#include "Base/OutputFlags.h"
#include <unordered_map>
#include <vector>
#include "Buffer/MemoryFileBuffer.h"
#include "Export.h"
#include "OcrProperty.h"
#include "OcrResult.h"


namespace detail
 {
	 
 }
/**
 * \brief Wrapper autour de MasterProcessingWorker permetant de masquer l'ensemble des libraries utilis� pour limit� les d�pendances
 */
class SHARED_EXPORT OcrAutomatorMaster
{
public:
	/**
	 * \brief Constructeur par d�faut
	 */
	OcrAutomatorMaster();
	/**
	 * \brief Destructeur par d�faut
	 */
	~OcrAutomatorMaster();

	/**
	 * \brief cr�er une instance du moteur d'OCR
	 * \param ocr nom de l'OCR
	 */
	void CreateFactory(std::string ocr);
	/**
	 * \brief attribue une valeur � une des propri�t�s au moteur d'OCR cr�er par CreateFactory
	 * \tparam T 
	 * \param prop nom de la propri�t�
	 * \param param valeur a attribuer
	 */
	template<typename T>
	void SetFactoryProperty(std::string prop, T param);
	/**
	 * \brief attribue une valeur � une des propri�t�s au moteur d'OCR cr�er par CreateFactory
	 * \param prop nom de la propri�t�
	 * \param param valeur a attribuer
	 */
	void SetFactoryProperty(std::string prop, std::string param);
	/**
	 * \brief attribue une valeur � une des propri�t�s au moteur d'OCR cr�er par CreateFactory
	 * \param prop nom de la propri�t�
	 * \param param valeur a attribuer
	 */
	void SetFactoryProperty(std::string prop, int param);
	/**
	 * \brief r�cup�re la valeur d'une des propri�t�s du moteur d'OCR cr�er par CreateFactory
	 * \param prop nom de la propri�t�
	 * \return valeur de la propri�t�
	 */
	std::string GetFactoryProperty(std::string prop);
	/**
	 * \brief cr�er une instance du moteur OcrAutomator et configure le moteur d'OCR
	 * \param ocr moteur d'OCR a utiliser
	 * \param parametersDefinition liste des propri�t� a d�finir avec leurs valeurs
	 * \param type Mode de fonctionnement du moteur OcrAutomator
	 * \param port Port r�seau pour la connexion entre le maitre et les esclaves
	 */
	void QuickSetup(std::string ocr, std::unordered_map<std::string, std::string> parametersDefinition, Docapost::IA::Tesseract::OutputFlags type = Docapost::IA::Tesseract::OutputFlags::None, int port = 12000);
	/**
	 * \brief cr�er une instance du moteur OcrAutomator avec le moteur d'OCR d�finit par CreateFactory
	 * \param type Mode de fonctionnement du moteur OcrAutomator
	 * \param port Port r�seau pour la connexion entre le maitre et les esclaves
	 */
	void CreateInstance(Docapost::IA::Tesseract::OutputFlags type = Docapost::IA::Tesseract::OutputFlags::None, int port = 12000);
	/**
	 * \brief Envoi une image au moteur OcrAutomator pour traitement
	 * \param id nom de l'image
	 * \param img binaire de l'image
	 * \param len taille du binaire de l'image
	 * \param s_uid uid unique attribu� a l'image
	 */
	void AddImage(std::string id, char* img, int len, std::string& s_uid);
	/**
	 * \brief Envoi un pdf au moteur OcrAutomator pour traitement
	 * \param id nom du pdf
	 * \param img binaire du pdf
	 * \param len taille du binaire du pdf
	 * \param s_uids uids unique attribu� au images apr�s conversion du PDF
	 * \return nombre de page du pdf
	 */
	int AddPdf(std::string id, char* img, int len, std::vector<std::string>& s_uids);
	/**
	 * \brief D�marre le syst�me et lance les threads d'OCRization
	 * \param maxThread 
	 * \param callback resultat de l'OCR et de l'extraction de l'image, si Docapost::IA::Tesseract::OutputFlags::MemoryImage est sp�cifi�, il est de ovtre r�ponsabilit� de lib�rer l'objet
	 */
	void Start(int maxThread, std::function<void(OcrResult*)> callback);
private:
	struct Impl;
	std::unique_ptr<Impl> d_ptr;
};

