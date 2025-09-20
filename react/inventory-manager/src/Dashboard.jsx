import { createElement, useState } from 'react'
import './dashboard.css'

function Item({name, count, onRemoveItem}) {
  const [isEditting, setIsEditting] = useState(false);

  const toggleisEditting = () => {
    setIsEditting(!isEditting)
  }

  const AAA = () => {
    if (isEditting) {
      return (
        <input type="text" placeholder={name}/>
      )
    }
    return (
      name + ": " + count
    )
  }

  return (
    <>
      <div>
        
        {AAA()}

        <button onClick={toggleisEditting}>
          ?
        </button>

        <button onClick={onRemoveItem}>
          -
        </button>
      </div>
    </>
  )
}

function ItemAdder({onAddNewItem}) {

  return (
    <>
      <button onClick={onAddNewItem}>
        +
      </button>
    </>
  )
}


function Dashboard() {
  const [items, setItems] = useState([]);

  const onAddNewItem = () => {
    const newItems = items.slice();
    newItems.push({name: "Item", count: 0});
    setItems(newItems);
  }

  const onRemoveItem = ({index}) => {
    const newItems = items.slice();
    newItems.splice(index, 1);
    setItems(newItems);
  }

  return (
    <>
      <div>
        Stock
        <div className='ItemList' id="ItemList">
          {items.map((item, index) => (
            <Item key={index} 
            name={item.name} 
            count={item.count} 
            onRemoveItem={() => onRemoveItem(index)}
            />
          ))}
          <ItemAdder onAddNewItem={onAddNewItem}/>
        </div>
      </div>
    </>
  )
}

export default Dashboard
