#pragma once

#include <QAbstractItemModel>
#include <QVariant>

#include "Services/Settings.h"
#include "SettingsNode.h"

namespace QmlApp
{
	enum SettingsDataRole
	{
		GroupRole = Qt::UserRole + 1,
		KeyRole,
		ValueRole
	};

	class SettingsModel : public QAbstractItemModel
	{
		Q_OBJECT

	public:
		explicit SettingsModel(Settings* settings = nullptr, QObject* parent = nullptr);
		~SettingsModel() override;

		// Required overrides for QAbstractItemModel
		QModelIndex index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
		QModelIndex parent(const QModelIndex& index) const override;
		int rowCount(const QModelIndex& parent = QModelIndex()) const override;
		int columnCount(const QModelIndex& parent = QModelIndex()) const override;
		QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
		bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
		Qt::ItemFlags flags(const QModelIndex& index) const override;
		QHash<int, QByteArray> roleNames() const override;

		// Custom methods to interact with settings
		[[nodiscard]] Q_INVOKABLE QVariant getValue(const QString& key,
													const QString& group = "General",
													const QVariant& default_value = QVariant()) const;
		Q_INVOKABLE void setValue(const QString& key, const QVariant& value, const QString& group = "General");

		Q_INVOKABLE void loadFromFile(const QString& file_path);
		Q_INVOKABLE void saveToFile(const QString& file_path);

	private:
		void load_settings_from_app_settings();

		SettingsNode* create_node(const QString& group, const QString& key, const QVariant& value, SettingsNode* parent = nullptr);
		[[nodiscard]] QList<SettingsNode*> get_leaf_nodes() const;
		void collect_leaf_nodes(SettingsNode* node, QList<SettingsNode*>& leaf_nodes) const;

		void reset();

	private:
		Settings* m_settings;
		bool m_sync_with_app_settings;
		SettingsNode* m_root_node;

	};
} // namespace QmlApp
