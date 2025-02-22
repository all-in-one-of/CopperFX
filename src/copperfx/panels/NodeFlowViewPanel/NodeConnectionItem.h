#ifndef NODE_CONNECTION_ITEM_H
#define NODE_CONNECTION_ITEM_H

#include <QSizeF>
#include <QPainter>
#include <QtCore/QUuid>
#include <QGraphicsItem>

namespace copper { namespace ui {

class NodeFlowScene;
class NodeSocketItem;

class NodeConnectionItem : public QGraphicsItem {
  public:
	//Q_OBJECT

	public:
		NodeConnectionItem(NodeFlowScene *scene);
    NodeConnectionItem(NodeFlowScene *scene, NodeSocketItem *socket_from, NodeSocketItem *socket_to);
    ~NodeConnectionItem() override;

    void setPosFrom(const QPointF &pos);
    void setPosTo(const QPointF &pos);
    void setSocketFrom(NodeSocketItem *socket_item);
    void setSocketTo(NodeSocketItem *socket_item);
    void updatePosFromSockets();
    NodeSocketItem* socketFrom() const;
    NodeSocketItem* socketTo() const;

  public:
    void hoverEnterEvent(QGraphicsSceneHoverEvent * event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event) override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
    QPainterPath shape() const override;

  private:
    QPainterPath buildPath() const;

  private:
    NodeFlowScene *_scene;
  	QPointF _pos_from;
    QPointF _pos_to;
    NodeSocketItem *_socket_from;
    NodeSocketItem *_socket_to;

    bool _connected = false;
    bool _hovered = false;
};

}}

#endif // NODE_CONNECTION_ITEM_H