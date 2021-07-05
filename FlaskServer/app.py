import datetime
from flask import Flask, request, flash, url_for, redirect, render_template
from flask_sqlalchemy import SQLAlchemy
from flask_restful import Resource, Api
from sqlalchemy import DateTime

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///plants.sqlite3'
app.config['SECRET_KEY'] = "BusanMeisterHighSchool"

api = Api(app)
db = SQLAlchemy(app)


class plants(db.Model):
    __tablename__ = 'plants'
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(100))
    cycle = db.Column(db.Integer)
    amount = db.Column(db.Integer)
    lastWater = db.Column(db.DateTime, default=datetime.datetime.utcnow)

    def __init__(self, name, cycle, amount):
        self.name = name
        self.cycle = cycle
        self.amount = amount
        return

@app.route('/')
def show_all():
    return render_template('show_all.html', plants=plants.query.all())

@app.route('/new', methods=['GET', 'POST'])
def new():
    if request.method == 'POST':
        if not request.form['name'] or not request.form['cycle'] or not request.form['amount']:
            flash('Please enter all the fields', 'error')
        else:
            plant = plants(request.form['name'], request.form['cycle'], request.form['amount'])

            db.session.add(plant)
            db.session.commit()
            flash('Record was successfully added')
            return redirect(url_for('show_all'))
    return render_template('new.html')


if __name__ == '__main__':
    db.create_all()
#    app.run(debug=True)
    app.run(host='0.0.0.0')


@app.route('/')
def hello_world():
    return 'Hello World!'


if __name__ == '__main__':
    app.run()


@app.route("/hello/<name>")
def home(name):
    return "Hello " + str(name);
