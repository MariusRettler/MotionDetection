#ifndef IFORM
#define IFORM


/**
 * @brief Die IForm Klasse, stellt ein Interface zur Vereinheitlichung der Form-Klassen dar.
 */
class IForm
{
public:
    /**
     * @brief Die Funktion OnShowUp wird bei jedem Aufruf der Form verwendet.
     */
    virtual void OnShowUp() = 0;

private:
    /**
     * @brief Die Funktion CreateActions erstellt die Aktionen.
     */
    virtual void CreateActions() = 0;

public slots:
    /**
     * @brief Der Slot setMinContourSize, setzt die minContourSize für die ImageServiceKlasse.
     */
    virtual void setMinContourSize(int value) = 0;

    /**
     * @brief Der Slot setThickness, setzt die Dicke der gezeichneten Kontur.
     */
    virtual void setThickness(int value) = 0;

};
#endif // IFORM
